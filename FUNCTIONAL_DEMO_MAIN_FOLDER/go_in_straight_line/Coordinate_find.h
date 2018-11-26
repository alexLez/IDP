

const int trigPinx = 9;
const int trigPiny = 10;
const int echoPinx = 11;
const int echoPiny = 12;
//defines zero coordinate and current coordinate
//int zero[2];
//int coordinate[2];
//int setup_or_loop = 0;
void xydistance();
float xdistance;
float ydistance;
float rolling_average_distancex[10]={0,0,0,0,0,0,0,0,0,0};
float rolling_average_distancey[10]={0,0,0,0,0,0,0,0,0,0};
#include <Servo.h>
Servo ultrasound_turner; 
const int ServoPin = 12;
int servo_angle=0;
void servo_ultrasound();
