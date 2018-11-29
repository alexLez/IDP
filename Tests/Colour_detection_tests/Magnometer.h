#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>


//initilise compass
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
float compass();
float relative_angle(float original_angle, float current_angle); //normalise for a nice value to put into the motor
//servo
