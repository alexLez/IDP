#include <Wire.h>
#include <Adafruit_MotorShield.h>


void motor_follow_angle(float current_angle,float desired_angle,int average_speed);
void turn_to_zero();
void turn(int turn_angle);
void stop_robot();
void turn_no_compass(int turn_time,int direction_turn,int turn_speed);
void reverse();
//set up motor
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *MotorLeft = AFMS.getMotor(2);
Adafruit_DCMotor *MotorRight = AFMS.getMotor(1);
int p_out ; //gain for motor control
