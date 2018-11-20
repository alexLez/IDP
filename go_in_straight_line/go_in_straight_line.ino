//include header file for various functions
#include "Coordinate_find.h"
#include "Motor_functions.h"
#include "Magnometer.h"
// define functions

//set the length in y direction of arena
float y_length;


//define the original direction and the current direction
float original_angle_compass;
float current_angle;


//define angle to follow
float angle_to_follow;

void setup() {
         Serial.begin(9600);
         Serial.println("Start");
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
        Serial.println(first_reading);
        Serial.println("original angle is:");
        Serial.println(original_angle_compass);
    
        //set up motors
        MotorLeft->run(RELEASE);
        MotorRight->run(RELEASE);
        AFMS.begin();  // create with the default frequency 1.6KHz for motors
}



 



void loop() {
        //get data
        
        current_angle = compass();
        current_angle=relative_angle(original_angle_compass,current_angle);//make it relative to original angle
   
        motor_follow_angle(current_angle, 0); 
        
     
          
        
        
          
        
        
        
  
}
