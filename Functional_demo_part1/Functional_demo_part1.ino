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
         delay(1000);
         //set up servo
         ultrasound_turner.attach(ServoPin);   //attach to a pin
         ultrasound_turner.write(0);  //initilise servo to 0
         //ultrasound pins
          pinMode(trigPinx, OUTPUT); // Sets the trigPin as an Output
          pinMode(echoPinx, INPUT); // Sets the echoPin as an Input
          pinMode(trigPinx, OUTPUT); // Sets the trigPin as an Output
          pinMode(echoPinx, INPUT); // Sets the echoPin as an Input
          pinMode(ServoPin, INPUT); // Sets the echoPin as an Input
         mag.begin(); //turn the magnometer on
      
        //read the original magnometer angle here and treat this is 0
        
         int first_reading = compass();
        //read the original magnometer angle here and treat this is 0
        int total_angle_Compass=0  ; //we will take the angle many times and take an average, excluding the first one as this is often wrong
        for (int i=1; i<=10; i+=1){
          total_angle_Compass+=compass();
          delay(100);
        }
        original_angle_compass = total_angle_Compass/10;
        //original_angle_compass=compass();
        Serial.println("original angle is:");
        Serial.println(original_angle_compass);

        xycoordinate();
        //set up motors
        MotorLeft->run(RELEASE);
        MotorRight->run(RELEASE);
        AFMS.begin();  // create with the default frequency 1.6KHz for motors
        angle_to_follow=0;
}



 



void loop() {
        //get data
        int i= 0;
        while(i<50){
        current_angle = compass();
        current_angle=relative_angle(original_angle_compass,current_angle);//make it relative to original angle
        motor_follow_angle(current_angle, angle_to_follow);
        //adjust servo
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
        i+=1;
        }
        
        stop_robot();
        
        turn(current_angle,40);
        //adjust servo
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
        stop_robot();
        angle_to_follow+=40;
        
        
     
          
        
        
          
        
        
        
  
}
