

  
    
void motor_follow_angle(float current_angle,float desired_angle){
         Serial.println("current_angle is:");
         Serial.println(current_angle);
         Serial.println("desired angle is:");
         Serial.println(desired_angle);
         int M_average = 100;
         int k_p=M_average/90;   //it should be full power when 90 degrees out and then decrease to half power when close to correct angle
         float e = current_angle-desired_angle; //if this is positive we are veering to the right
         Serial.println("error is");
         Serial.println(e);
         int p_out = k_p*e;  //set gain
         int right_motor_out = M_average +p_out;
         int left_motor_out = M_average -p_out;
         MotorLeft->setSpeed(left_motor_out);
         MotorLeft->run(FORWARD); 
         MotorRight->setSpeed(right_motor_out);
         MotorRight->run(FORWARD); 
         
         
}


//turn x degrees
void turn(int current_angle, int turn_angle){
    float target_angle = current_angle+turn_angle;
    while (abs(target_angle-compass())>5);
         {
                 int M_average = 100;
                 int k_p = 150/90;
                 float e = target_angle-current_angle;
                 int p_out = e*k_p;
                 int direction_turn = e/abs(e);
                 int left_motor_out = (M_average +p_out);
                 int right_motor_out = (M_average +p_out);
                 if (direction_turn==1){
                 MotorLeft->setSpeed(left_motor_out);
                 MotorLeft->run(FORWARD); 
                 MotorRight->setSpeed(right_motor_out);
                 MotorRight->run(BACKWARD);
                 }
                 else{
                 MotorLeft->setSpeed(left_motor_out);
                 MotorLeft->run(BACKWARD); 
                 MotorRight->setSpeed(right_motor_out);
                 MotorRight->run(FORWARD);
                 }
         } 
}
//stop function
void stop_robot(){
         MotorLeft->setSpeed(0);
         MotorLeft->run(FORWARD); 
         MotorRight->setSpeed(0);
         MotorRight->run(FORWARD);
}

void turn_no_compass(int turn_time,int direction_turn){   //driection turn = 1 for right and -1 for left, turn time in secs
                 int left_motor_out=255*direction_turn;
                 int right_motor_out=255*direction_turn*(-1);
                 MotorLeft->setSpeed(left_motor_out);
                 MotorLeft->run(FORWARD); 
                 MotorRight->setSpeed(right_motor_out);
                 MotorRight->run(FORWARD);
                 delay(turn_time*1000);
                 MotorLeft->setSpeed(0);
                 MotorLeft->run(FORWARD); 
                 MotorRight->setSpeed(0);
                 MotorRight->run(FORWARD);
}
  
