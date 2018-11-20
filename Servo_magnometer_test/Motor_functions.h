#include <Wire.h>
#include <Adafruit_MotorShield.h>


void motor_follow_angle(float current_angle,float desired_angle);
void turn(int current_angle, int turn_angle);
void stop_robot();
void turn_no_compass(int turn_time,int direction_turn);
//set up motor
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *MotorLeft = AFMS.getMotor(2);
Adafruit_DCMotor *MotorRight = AFMS.getMotor(1);
int p_out ; //gain for motor control
