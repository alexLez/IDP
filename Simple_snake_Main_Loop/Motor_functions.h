#include <Wire.h>
#include <Adafruit_MotorShield.h>


void motor_follow_angle(float current_angle,float desired_angle,int average_speed);   //a control algorithm - input the current angle, the angle we want to follow, and the average speed needed, and the motors adjust to go towards this angle
void turn(int turn_angle);   //turn by a specified angle
void stop_robot();    
void turn_no_compass(int turn_time,int direction_turn,int turn_speed);  //turn based on time rather than relying on magnometer
void reverse(); //reverse function
int angle_to_turn;//decide how far to turn at each point so as to always be going 0 or 180 during the snake and avoid error propagation
void angle_turn(int desired_angle); //set the angle we need to turn through the angle we are currently at and the angle we want to get too
//set up motor
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *MotorLeft = AFMS.getMotor(2);
Adafruit_DCMotor *MotorRight = AFMS.getMotor(1);

int p_out ; //gain for motor control
