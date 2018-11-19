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
float current_angle1;
float current_angle2;
float current_angle3;

//define angle to follow
float angle_to_follow;

void setup() {
         Serial.begin(9600);
        delay(10000);
          
                mag.begin(); //turn the magnometer on
      
        //read the original magnometer angle here and treat this is 0
        current_angle1 = compass();
        Serial.println(current_angle1);
        delay(25);
        current_angle2 = compass();
        Serial.println(current_angle2);
        delay(25);
        current_angle3 = compass();
        Serial.println(current_angle3);

          original_angle_compass = (current_angle1+current_angle2+current_angle3)/3;
        //original_angle_compass=compass();
        Serial.println("original angle is:");
        Serial.println(original_angle_compass);
    
        
       

      
        delay(1000);
        //set up motors
        MotorLeft->run(RELEASE);
        MotorRight->run(RELEASE);
        AFMS.begin();  // create with the default frequency 1.6KHz for motors
}



 



void loop() {
        //get data
        delay(25);        
        current_angle1 = compass();
        delay(25);
        current_angle2 = compass();
        delay(25);
        current_angle3 = compass();
        current_angle = (current_angle1+current_angle2+current_angle3)/3;
        Serial.println(current_angle);
        //find current angle here using magnometer and the difference from the 0 point
       // current_angle = compass()-original_angle_compass;
        //angle_to_follow = current_angle;
        //colour = update the colour with what is detected by the ultrasound
        //update the angle we must turn towards if it is a yellow mine

        motor_follow_angle(current_angle, original_angle_compass); 
        //delay(5000);         
        //current_angle = compass()-original_angle_compass;
        //turn(current_angle, 90);
          
        
        
          
        
        
        
  
}
