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
        
        
        //set up motors
        MotorLeft->run(RELEASE);
        MotorRight->run(RELEASE);
        AFMS.begin();  // create with the default frequency 1.6KHz for motors
        
      
        //read the original magnometer angle here and treat this is 0
        original_angle_compass=compass();
        
    
        //set up magnometer
        mag.begin(); //turn the magnometer on
        xycoordinate();    //find the coordinate at the start point and set this to 0

        //define angle to follow as directly straight forward
        angle_to_follow = 0;
        
}





void loop() {
        //get data
          
        //find current angle here using magnometer and the difference from the 0 point
        current_angle = compass()-original_angle_compass;
        angle_to_follow = current_angle;
        //colour = update the colour with what is detected by the ultrasound
        //update the angle we must turn towards if it is a yellow mine
       
        motor_follow_angle(current_angle, angle_to_follow); 
        delay(5000);         
        current_angle = compass()-original_angle_compass;
        turn(current_angle, 90);
          
        
        
          
        
        
        
  
}
