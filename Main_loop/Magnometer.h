#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>


//initilise compass
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
float compass();

//servo

#include <Servo.h>
Servo ultrasound_turner; 
const int ServoPin = 12;
