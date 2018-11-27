//include header file for various functions
#include "Coordinate_find.h"
#include "Motor_functions.h"
#include "Magnometer.h"
#include "colour.h"
// define functions

//set the length in y direction of arena
float y_length=200;
float x_length=200;

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



void setup() {
         Serial.begin(9600);
         Serial.print("start");
          
         //magnometer set up   
         mag.begin(); //turn the magnometer on

         pinMode(trigPinx, OUTPUT); // Sets the trigPin as an Output
          pinMode(echoPinx, INPUT); // Sets the echoPin as an Input
          pinMode(trigPiny, OUTPUT); // Sets the trigPin as an Output
          pinMode(echoPiny, INPUT); // Sets the echoPin as an Input
         
         
        //read the original magnometer angle here and treat this as 0
        int total_angle_Compass=0  ; //we will take the angle many times and take an average, excluding the first one as this is often wrong
        for (int i=1; i<=10; i+=1){
          total_angle_Compass+=compass();
          delay(50);
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
        
        
        current_angle=relative_angle(original_angle_compass,compass());
        angle_to_follow=current_angle;
        Serial.println("start");
        colour=0;
        direction_facing=1;
}



 



void loop() {
        //get data

        //get the current angle and make it relative to the original angle on a -180 to 180 scale
        current_angle=relative_angle(original_angle_compass,compass());
        Serial.println("current_angle");
        Serial.println(current_angle);
        motor_follow_angle(current_angle, angle_to_follow); 
        //find_current_colour_and_show();
        xydistance();
        Serial.println("ydistance");
        Serial.println(y_length-ydistance);
        if ((y_length-ydistance)<=30){
          stop_robot();
          if (direction_facing==1){
            turn(90);
            stop_robot();
            delay(1000);
            current_angle=relative_angle(original_angle_compass,compass());
            delay(1000);
            motor_follow_angle(current_angle,90);
            delay(2000);
            stop_robot();
            delay(1000);
            turn(90);
            delay(2000);
            current_angle=relative_angle(original_angle_compass,compass());
            angle_to_follow=180;
            motor_follow_angle(current_angle,angle_to_follow);
            
            direction_facing=-1; //set it so we are now going in the other direction to the original direction
            
          }
          else{
           
            turn(-90);
            stop_robot();
            delay(1000);
            current_angle=relative_angle(original_angle_compass,compass());
            delay(1000);
            motor_follow_angle(current_angle,90);
            delay(2000);
            stop_robot();
            delay(1000);
            turn(-90);
            delay(2000);
            current_angle=relative_angle(original_angle_compass,compass());
            angle_to_follow=0;
            motor_follow_angle(current_angle,angle_to_follow);
            direction_facing = 1;  //set it so we are going in original direction again
          
          }
          
        }
        
        if (colour==0){
           // servo angle+=5;
            //pass and keep going as we are
        }

       else if (colour==2){   //yellow
              //essentially pass and just keep moving forward
       }
       else if (colour==3){//red
               //we are currently stationary so reverse for a couple of secs then move off
             MotorLeft->setSpeed(50);   
             MotorLeft->run(BACKWARD); 
             MotorRight->setSpeed(50);
             MotorRight->run(BACKWARD); 
             delay(2000);
             stop_robot();
             delay(1000);
             find_coordinate();
             
             //go around the red mine to the left where we know it is safe if we are going up, and to the right if we are going down
             if (direction_facing==1){
             turn(-45);
             stop_robot();
             current_angle=relative_angle(original_angle_compass,compass());
             delay(1000);
             motor_follow_angle(current_angle,-45);
             delay(3000);
             stop_robot();
             delay(1000);
             turn(90);
             stop_robot();
             current_angle=relative_angle(original_angle_compass,compass());
             delay(1000);
             motor_follow_angle(current_angle,45);
             delay(3000);
             turn(-45);
             current_angle=relative_angle(original_angle_compass,compass());
             motor_follow_angle(current_angle,0);
             angle_to_follow=0;
             }
             else {
                  turn(45);
                 stop_robot();
                 current_angle=relative_angle(original_angle_compass,compass());
                 delay(1000);
                 motor_follow_angle(current_angle,-135);
                 delay(3000);
                 stop_robot();
                 delay(1000);
                 turn(-90);
                 stop_robot();
                 current_angle=relative_angle(original_angle_compass,compass());
                 delay(1000);
                 motor_follow_angle(current_angle,135);
                 delay(3000);
                 turn(45);
                 current_angle=relative_angle(original_angle_compass,compass());
                 motor_follow_angle(current_angle,180);
                 angle_to_follow=180;
             }
             
           
             //now move on and use other checks
             find_coordinate();
        
       }
       colour=0;//reset it to black once manouver has been completed  
       
      
      
        }
          
        
        
          
        
        
        
  
