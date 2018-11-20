

  
    
void motor_follow_angle(float current_angle,float desired_angle){
         
         int M_average = 100;
         int k_p_large=5; //for when it is out by more than 5
         int k_p_small=5;  //for when it is only a small deviation
         float e = current_angle-desired_angle; //if this is positive we are veering to the right so increase right motor
         if (e<-180){      //this normalises the angle difference as we have a angle 'clock' that goes -180 to 180
          e+=360;
         }
         if (e>180){
          e-=360;
         }
         if (-5 <e and e<5){
         p_out = k_p_small*e;
         }
         else{
         p_out = k_p_large*e;  //set gain
         }
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


//turn x degrees
void turn(int current_angle, int turn_angle){
    int direction_turn = turn_angle/abs(turn_angle);  //positive is clockwise and negative is AC 
    float target_angle = current_angle+turn_angle;
    if (target_angle<-180){      //this normalises the angle difference as we have a angle 'clock' that goes -180 to 180
          target_angle+=360;
    }
    if (target_angle>180){
        target_angle-=360;
    }
    float e=current_angle-target_angle;
    if (e<-180){      //this normalises the angle difference as we have a angle 'clock' that goes -180 to 180
          e+=360;
    }
    if (e>180){
        e-=360;
    }
    int M_average = 100;
    int k_p = 10;
    while (-direction_turn*(e)>5){   //while we are over 5 degrees from the angle we want to be at use the proportional control to get there
               
                 int p_out = abs(e*k_p); //absolute as we don't want either to slow down from M_average so they only get faster as e increase - sign does not matter
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
                 current_angle = relative_angle(original_angle_compass, current_angle);
                 e = target_angle-current_angle;
                 if (e<-180){      //this normalises the angle difference as we have a angle 'clock' that goes -180 to 180
                      e+=360;
                 }
                 if (e>180){
                      e-=360;
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
  
