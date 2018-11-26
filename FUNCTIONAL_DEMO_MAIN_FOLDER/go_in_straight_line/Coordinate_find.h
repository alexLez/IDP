

const int trigPinx = 9;
const int trigPiny = 10;
const int echoPinx = 11;
const int echoPiny = 12;
int coordinate[2]={0,0};
void find_coordinate();
void xydistance();
float xdistance;
float ydistance;
#include <Servo.h>
Servo ultrasound_turner; 
const int ServoPin = 12;
int servo_angle=0;
void servo_ultrasound();
