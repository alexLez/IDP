//include header file for various functions
#include "Coordinate_find.h"
#include "Motor_functions.h"
#include "Magnometer.h"
// define functions

float original_angle_compass;
float current_angle;

void setup() {
       
        //set up servo
        ultrasound_turner.attach(ServoPin);   //attach to a pin
        ultrasound_turner.write(0);  //initilise servo to 0
        
        
        //read the original magnometer angle here and treat this is 0
        original_angle_compass=compass();
       
        
        
        //set up magnometer
        mag.begin(); //turn the magnometer on     
        
}






void loop() {
        //get data
          
        //find current angle here using magnometer and the difference from the 0 point
        current_angle = compass()-original_angle_compass;
        if (current_angle<180){
              ultrasound_turner.write(current_angle); //turn the servo to face the direction original direction
              
        }
        else{
              ultrasound_turner.write(current_angle-180);   //as servo only turns 180 degrees so we will need to reset it when it turns past here to keep perpendicular
             
        }
       
        
        
        
  
}
