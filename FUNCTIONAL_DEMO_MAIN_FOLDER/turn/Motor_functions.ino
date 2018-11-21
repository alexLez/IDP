


    
void motor_follow_angle(float current_angle,float desired_angle){
         Serial.println("current_angle is:");
         Serial.println(current_angle);
         Serial.println("desired angle is:");
         Serial.println(desired_angle);
         int M_average = 100;
         int k_p_large=7; //for when it is out by more than 5
         int k_p_small=7;  //for when it is only a small deviation
         float e = current_angle-desired_angle; //if this is positive we are veering to the right
         Serial.println("error is");
         Serial.println(e);
         
         
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
         Serial.println(left_motor_out);
         Serial.println(right_motor_out);
         
         
         
}

 //turn x degrees
void turn(int current_angle, int turn_angle){
    
    float target_angle = current_angle+turn_angle;
    float e =(target_angle-relative_angle(original_angle_compass,compass()));
      
      Serial.print("Error");
      Serial.println(e);
      
    while ((e)>5)   //while we are over 5 degrees from the angle we want to be at use the proportional control to get there
         {      
                 int M_average = 100;
                 int k_p = 5;
                 
                 Serial.println(e); 
                 int p_out = e*k_p;
                 int direction_turn = e/abs(e);
                 int left_motor_out = (M_average +p_out);
                 int right_motor_out = (M_average +p_out);
                 if (right_motor_out>255){
                    right_motor_out=255;
                 }
                 if (left_motor_out>255){
                    left_motor_out=255;
         }
                 if (direction_turn==1){
                 MotorLeft->setSpeed(left_motor_out);
                 MotorLeft->run(FORWARD); 
                 MotorRight->setSpeed(right_motor_out);
                 MotorRight->run(BACKWARD);
                 Serial.println(left_motor_out);
                 Serial.println(right_motor_out);
                 }
                 else{
                 MotorLeft->setSpeed(left_motor_out);
                 MotorLeft->run(BACKWARD); 
                 MotorRight->setSpeed(right_motor_out);
                 MotorRight->run(FORWARD);
                 Serial.println(left_motor_out);
                 Serial.println(right_motor_out);
                 
                 }
                current_angle = relative_angle(original_angle_compass,compass());
                e = (target_angle-current_angle);
                
                
         } 
         
}
//stop function
void stop_robot(){
         MotorLeft->setSpeed(0);
         MotorLeft->run(FORWARD); 
         MotorRight->setSpeed(0);
         MotorRight->run(FORWARD);
}
 void turn_no_compass(double turn_time,int direction_turn){   //driection turn = 1 for right and -1 for left, turn time in secs
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
