//include header file for various functions
#include "Coordinate_find.h"
#include "Motor_functions.h"
#include "Magnometer.h"
#include "colour.h"
// define functions

//set the length in y direction of arena
float y_length;
float x_length;

int LED_YELLOW=44;
int LED_RED=46;

//define the original direction and the current direction
float original_angle_compass;
float current_angle;

int colour=0;
int Pin1=A9;
int Pin2=A9;
int Pin3=A9;
float BlackRef1;
float BlackRef2;
float BlackRef3;
float rolling_colour1[10]={0,0,0,0,0,0,0,0,0,0};  //create a colour array full of zeros
float rolling_colour2[10]={0,0,0,0,0,0,0,0,0,0};  //create a colour array full of zeros
float rolling_colour3[10]={0,0,0,0,0,0,0,0,0,0};  //create a colour array full of zeros
float rolling_average1=0;
float rolling_average2=0;
float rolling_average3=0;
float instantaneous_reading_average1;
float instantaneous_reading_average2;
float instantaneous_reading_average3;
//define angle to follow
float angle_to_follow;
int rand_turn_time;

void setup() {
         Serial.begin(9600);
         Serial.print("start of setup");
         
         //magnometer set up   
         mag.begin(); //turn the magnometer on
         
         
        
        
        //LED pin set up
        pinMode(LED_RED, OUTPUT);
        pinMode(LED_YELLOW, OUTPUT);
        
        
        rolling_average_reset();
        int initial_turn_time = 1.5;
        

        //set up average for the distances from the walls
        Serial.print("end of setup");
        
}



 



void loop() {
        //get data

        //get the current angle and make it relative to the original angle on a -180 to 180 scale
        
        
        find_current_colour_and_show(10,20,150,10,20,150,10,20,150);   //vary the thresholds here
        
      
      
      
        }
          
        
        
          
        
        
        
  
