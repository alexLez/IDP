//include header file for various functions
#include "Coordinate_find.h"
#include "Motor_functions.h"
#include "Magnometer.h"
#include "colour.h"
#include "LED.h"
// define functions

//set the length in y direction of arena
float y_length;
//define LED pins here
const int LED_RED_PIN= 6;
const int LED_YELLOW_PIN=7;

//define the original direction and the current direction
float original_angle_compass;
float current_angle;

//define the colour function stuff
int colour;
int Pin1=A0;
int BlackRef;
float rolling_colour[10]={0,0,0,0,0,0,0,0,0,0};  //create a colour array full of zeros
float rolling_average;
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
        pinMode(LED_RED_PIN, OUTPUT);
        pinMode(LED_YELLOW_PIN, OUTPUT);
        
        
       //fill the colour array with the value of black detected at the start in 0.01 sec time intervals
        for (int i=0;i<10;i+=1){
          rolling_colour[i]=light_levels(Pin1);
          delay(100);
        }
}



 



void loop() {
        //get data
        current_angle = compass();
        current_angle=relative_angle(original_angle_compass,current_angle);//make it relative to original angle
        
        //find the current colour
        for (int i=0;i<9;i+=1){    //all the avlues in array down by one - the most recent level is put at the end
          rolling_colour[i]=rolling_colour[i+1];
        }
        rolling_colour[9] = light_levels(Pin1);
        rolling_average = array_average(rolling_colour);//this is the rolling average of the first 8 values so we can compare the final 2 values to check if there is a new colour detected-having 2 values will hopefully remove a little bit of noise  
        BlackRef = rolling_average;  // set the reference level for what we think is normal to be the average levels we are seeing and we move along
        if (((rolling_colour[9]+rolling_colour[8])/2)>rolling_average+3){    //the 50 is just the minimum that may be a mine as it is a significant jump
             MotorLeft->setSpeed(30);   //slow right down and approach slowly
             MotorLeft->run(FORWARD); 
             MotorRight->setSpeed(30);
             MotorRight->run(FORWARD);
             delay(500); //delay one second until we are closer in and will hopefully be able to see the full mine
             stop_robot();
             delay(100); 
             float light_levels_used=light_levels(Pin1);  //measure the light levels here
             if (light_levels_used>BlackRef+5 and light_levels_used<BlackRef+100){    //this is only for yellow and red at the moment
              colour = 2 ;   //say it is yellow
              delay(10000);
             }
             if (light_levels_used>=BlackRef+3 and light_levels_used>BlackRef+6){
              colour = 3;  //say it is red
              delay(10000);
             }
             else {
              colour=0;
             }
              
             
        }

        
        if (colour ==0){
        motor_follow_angle(current_angle, 0); 
        }
        if (colour==2){
          stop_robot();
          LED(2);
          delay(10000);
        }
        if (colour==3){
          stop_robot();
          LED(3);
          delay(10000);
        }
     
          
        
        
          
        
        
        
  

}
