

  
    
void motor_follow_angle(float current_angle,float desired_angle){

         int M_average = 30;
         int k_p_large=7; //for when it is out by more than 5
         int k_p_small=7;  //for when it is only a small deviation
         float e = current_angle-desired_angle; //if this is positive we are veering to the right

         
         
         p_out = k_p_large*e;  //set gain
         
         int right_motor_out = M_average +p_out;
         int left_motor_out = M_average -p_out;
         if (right_motor_out>255){
            right_motor_out=255;
         }
         if (left_motor_out>255){
            left_motor_out=255;
         }
         if (right_motor_out<0){
            right_motor_out=0;
         }
         if (left_motor_out<0){
            left_motor_out=0;
         }
         MotorLeft->setSpeed(left_motor_out);
         MotorLeft->run(FORWARD); 
         MotorRight->setSpeed(right_motor_out);
         MotorRight->run(FORWARD); 
         
         
         
         
}

         

//stop function
void stop_robot(){
         MotorLeft->setSpeed(0);
         MotorLeft->run(FORWARD); 
         MotorRight->setSpeed(0);
         MotorRight->run(FORWARD);
}

void turn_no_compass(int turn_time,int direction_turn,int turn_speed){   //driection turn = 1 for right and -1 for left, turn time in secs, and turn speed out of 255
                 int left_motor_out=turn_speed;
                 int right_motor_out=turn_speed;
                 MotorLeft->setSpeed(left_motor_out);
                 MotorLeft->run(FORWARD); 
                 MotorRight->setSpeed(right_motor_out);
                 MotorRight->run(BACKWARD);
                 delay(turn_time*1000);
                 MotorLeft->setSpeed(0);
                 MotorLeft->run(FORWARD); 
                 MotorRight->setSpeed(0);
                 MotorRight->run(FORWARD);
                 delay(2000);
                 current_angle=relative_angle(original_angle_compass,compass());
}
  
