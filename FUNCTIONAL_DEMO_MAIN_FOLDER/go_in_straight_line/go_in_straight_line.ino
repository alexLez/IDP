//include header file for various functions
#include "Coordinate_find.h"
#include "Motor_functions.h"
#include "Magnometer.h"
#include "colour.h"
// define functions

//set the length in y direction of arena
float y_length;
float x_length;

int LED_YELLOW=44;
int LED_RED=46;

//define the original direction and the current direction
float original_angle_compass;
float current_angle;

int colour=0;
int Pin1=A0;
int Pin2 = A1;
int Pin3=A2;
float BlackRef1;
float BlackRef2;
float BlackRef3;
float rolling_colour1[10]={0,0,0,0,0,0,0,0,0,0};  //create a colour array full of zeros
float rolling_colour2[10]={0,0,0,0,0,0,0,0,0,0};  //create a colour array full of zeros
float rolling_colour3[10]={0,0,0,0,0,0,0,0,0,0};  //create a colour array full of zeros
float rolling_average1;
float rolling_average2;
float rolling_average3;
float instantaneous_reading_average1;
float instantaneous_reading_average2;
float instantaneous_reading_average3;
//define angle to follow
float angle_to_follow;
int rand_turn_time;

bool forward_sweep = true;
int count = 0;
bool wall = false;

void setup() {
         Serial.begin(9600);
         
         
         //magnometer set up   
         mag.begin(); //turn the magnometer on
         
         
        //read the original magnometer angle here and treat this as 0
        int total_angle_Compass=0  ; //we will take the angle many times and take an average, excluding the first one as this is often wrong
        for (int i=1; i<=10; i+=1){
          total_angle_Compass+=compass();
          delay(100);
        }
        
        original_angle_compass = total_angle_Compass/10;

        //LED pin set up
        pinMode(LED_RED, OUTPUT);
        pinMode(LED_YELLOW, OUTPUT);
        
        //set up motors
        
        MotorLeft->run(RELEASE);
        MotorRight->run(RELEASE);
        AFMS.begin();  // create with the default frequency 1.6KHz for motor
        rolling_average_reset();
        int initial_turn_time = 1.5;
        turn_no_compass(initial_turn_time,1,255);
        current_angle=relative_angle(original_angle_compass,compass());
        angle_to_follow=current_angle;

        //set up average for the distances from the walls
        for (int a=1;a<10;a++){
          xydistance();
          rolling_average_distancex[a]=xdistance;
          rolling_average_distancey[a]=ydistance;
        }
        
}



 



void loop() {
        //get data

        //get the current angle and make it relative to the original angle on a -180 to 180 scale
        current_angle=relative_angle(original_angle_compass,compass());
        motor_follow_angle(current_angle, angle_to_follow); 
        find_current_colour_and_show();
        //Serial.println("aaaa");
        if (colour==0){
           // servo angle+=5;
            //pass and keep going as we are
        }

       else if (colour==2){   //yellow
              //we are currently stationary somove forward for a couple of secs
              MotorLeft->setSpeed(30);   
             MotorLeft->run(FORWARD); 
             MotorRight->setSpeed(30);
             MotorRight->run(FORWARD);
             delay(2000);
             stop_robot(); //leave the angle to follow the same as it is for now
      
       }
       else if (colour==3){
               //we are currently stationary so reverse for a couple of secs then move off
              MotorLeft->setSpeed(50);   
             MotorLeft->run(BACKWARD); 
             MotorRight->setSpeed(50);
             MotorRight->run(BACKWARD); 
             delay(2000);
             stop_robot();
             delay(1000);
             rand_turn_time = random(1.5,4.5);
             turn_no_compass(rand_turn_time,-1,255);
             current_angle=relative_angle(original_angle_compass,current_angle);
             angle_to_follow=current_angle;
             motor_follow_angle(current_angle,angle_to_follow);
             //now move on and use other checks
        
       }
       colour=0;//reset it to black once manouver has been completed  
      
      
      
        }
          
        
        
          
        
        
        
  
