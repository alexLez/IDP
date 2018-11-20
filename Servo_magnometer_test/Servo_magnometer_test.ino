//include header file for various functions
#include "Coordinate_find.h"
#include "Motor_functions.h"
#include "Magnometer.h"
// define functions

float original_angle_compass;
float current_angle;

void setup() {
       Serial.begin(9600);
         
        //set up servo
        ultrasound_turner.attach(ServoPin);   //attach to a pin
        ultrasound_turner.write(0);  //initilise servo to 0
        delay(1000);
        mag.begin(); //turn the magnometer on
        //read the original magnometer angle here and treat this is 0
        original_angle_compass=compass();
       
        Serial.println(original_angle_compass);
        
        //set up magnometer
             
        
}






void loop() {
        //get data
         
        //find current angle here using magnometer and the difference from the 0 point
        current_angle = relative_angle(original_angle_compass,compass());
       Serial.println(current_angle);
        if (current_angle<3){
              ultrasound_turner.write(current_angle+180); //turn the servo to face the direction original direction
              
        }
        else{
              ultrasound_turner.write(current_angle);   //as servo only turns 180 degrees so we will need to reset it when it turns past here to keep perpendicular
             
        }
       
        
        
        
  
}
