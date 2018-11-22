//include header file for various functions
#include "Coordinate_find.h"
#include "Motor_functions.h"
#include "Magnometer.h"
#include "colour.h"
// define functions

//set the length in y direction of arena
float y_length;


//define the original direction and the current direction
float original_angle_compass;
float current_angle;

int colour;
int Pin1=A0;
int BlackRef;
float rolling_colour[10]={0,0,0,0,0,0,0,0,0,0};  //create a colour array full of zeros
float rolling_average;
//define angle to follow
float angle_to_follow;

void setup() {
         Serial.begin(9600);
         //Serial.println("Start");
         delay(1000);
        
         mag.begin(); //turn the magnometer on
        int first_reading = compass();
        //read the original magnometer angle here and treat this is 0
        int total_angle_Compass=0  ; //we will take the angle many times and take an average, excluding the first one as this is often wrong
        for (int i=1; i<=10; i+=1){
          total_angle_Compass+=compass();
          delay(100);
        }
        original_angle_compass = total_angle_Compass/10;
        //original_angle_compass=compass();
        //Serial.println(first_reading);
        //Serial.println("original angle is:");
        //Serial.println(original_angle_compass);

        pinMode(44, OUTPUT);
        pinMode(46, OUTPUT);
        //set up motors
        MotorLeft->run(RELEASE);
        MotorRight->run(RELEASE);
        AFMS.begin();  // create with the default frequency 1.6KHz for motors
        MotorLeft->setSpeed(30);   //slow right down and approach slowly
             MotorLeft->run(FORWARD); 
             MotorRight->setSpeed(30);
             MotorRight->run(FORWARD);
        delay(1000);
        for (int i=0;i<10;i+=1){    //all the avlues in array down by one - the most recent level is put at the end
          rolling_colour[i]=light_levels(Pin1);
        }
}



 



void loop() {
        //get data
        
        current_angle = compass();
        current_angle=relative_angle(original_angle_compass,current_angle);//make it relative to original angle
   
        motor_follow_angle(current_angle, 0); 
        //find the current colour
        for (int i=0;i<9;i+=1){    //all the avlues in array down by one - the most recent level is put at the end
          rolling_colour[i]=rolling_colour[i+1];
        }
        rolling_colour[9] = light_levels(Pin1);
        rolling_average = array_average(rolling_colour);//this is the rolling average of the first 8 values so we can compare the final 2 values to check if there is a new colour detected-having 2 values will hopefully remove a little bit of noise  
        BlackRef = rolling_average;  // set the reference level for what we think is normal to be the average levels we are seeing and we move along
        Serial.println("Rolling_average");
        Serial.println(rolling_average);
        if (((rolling_colour[9]+rolling_colour[8])/2)>rolling_average+2  ){    //the 50 is just the minimum that may be a mine as it is a significant jump
             MotorLeft->setSpeed(10);   //slow right down and approach slowly
             MotorLeft->run(FORWARD); 
             MotorRight->setSpeed(10);
             MotorRight->run(FORWARD);
             delay(1000); //delay one second until we are closer in and will hopefully be able to see the full mine
             stop_robot();
             delay(1000); 
             float light_levels_used=light_levels(Pin1);  //measure the light levels here
             if (light_levels_used>BlackRef+70){    //this is only for yellow and red at the moment
              colour = 2 ;
              Serial.println("Yellow");//say it is yellow
              Serial.println(analogRead(A0));
              digitalWrite(44,HIGH);
              rolling_colour[8]=rolling_colour[1];
              rolling_colour[9]=rolling_colour[1];
              
              
              delay(10000);
              digitalWrite(44,LOW);
             }
             else if (light_levels_used>BlackRef+20){
              colour = 3;  //say it is red
              
              Serial.println("Red");
              Serial.println(analogRead(A0));
              digitalWrite(46,HIGH);
              delay(10000);
              digitalWrite(46,LOW);
              rolling_colour[8]=rolling_colour[1];
              rolling_colour[9]=rolling_colour[1];
             }
        Serial.println(analogRead(A0));
        
        }
          
        
        
          
        
        
        
  
}
