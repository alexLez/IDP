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
        
        
        //set up servo
        ultrasound_turner.attach(ServoPin);   //attach to a pin
        ultrasound_turner.write(0);  //initilise servo to 0
        
        
        //read the original magnometer angle here and treat this is 0
        original_angle_compass=compass();
        
        
        //ultrasound pins
        pinMode(trigPinx, OUTPUT); // Sets the trigPin as an Output
        pinMode(echoPinx, INPUT); // Sets the echoPin as an Input
        pinMode(trigPinx, OUTPUT); // Sets the trigPin as an Output
        pinMode(echoPinx, INPUT); // Sets the echoPin as an Input
        pinMode(ServoPin, INPUT); // Sets the echoPin as an Input
        Serial.begin(9600); // Starts the serial communication
        
        
        //set up magnometer
        mag.begin(); //turn the magnometer on
        xycoordinate();    //find the coordinate at the start point and set this to 0

        //define angle to follow as directly straight forward
        angle_to_follow = 0;

        Serial.begin(9600);
}






void loop() {
        //get data
          
        //find current angle here using magnometer and the difference from the 0 point
        current_angle = compass()-original_angle_compass;
        if (current_angle<180){
              ultrasound_turner.write(current_angle); //turn the servo to face the direction original direction
              //find coordinates relative to (0,0), i.e. the start point - updates the coordinate
              xycoordinate();
        }
        else{
              ultrasound_turner.write(current_angle-180);   //as servo only turns 180 degrees so we will need to reset it when it turns past here to keep perpendicular
              //find coordinates relative to (0,0), i.e. the start point - updates the coordinate
              xycoordinate();   //we need to set x=y and y= y_length -x as the servo cant magnometer
              int x = coordinate[0];
              int y=coordinate[1];
              coordinate[0]=y;
              coordinate[1]=y_length-x;
        }
        //print coordinate location after the turn
        Serial.println("("); Serial.println(coordinate[0]); Serial.println(coordinate[1]); Serial.println(")");
        //drive round in a square
        angle_to_follow = current_angle;
        //colour = update the colour with what is detected by the ultrasound
        //update the angle we must turn towards if it is a yellow mine
       
        motor_follow_angle(current_angle, angle_to_follow); 
        delay(5000);         
        current_angle = compass()-original_angle_compass;
        turn(current_angle, 90);
        
        
        
  
}
