int direction_facing = 1; //1 for facing forwards and -1 for facing the other way

const int trigPinx = 10;
const int trigPiny = 9;
const int echoPinx = 12;
const int echoPiny = 11;
int coordinate[2]={0,0};
void find_coordinate();
void xydistance();
float xdistance;
float ydistance;
#include <Servo.h>
Servo ultrasound_turner; 
const int ServoPin = 12;
int servo_angle=0;

int xcoordinate=0;
int ycoordinate=0;
