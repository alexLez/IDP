

  
    
void motor_follow_angle(float current_angle,float desired_angle){

         int M_average = 100;
         int k_p_large=7; //for when it is out by more than 5
         int k_p_small=7;  //for when it is only a small deviation
         
        float e = current_angle-desired_angle; //if this is positive we are veering to the right
        if (e>180){    //coreect for when we are at different sides of the compass
          e = e-360;
        }
        if (e<-180){
          e=e+360;
        }
         Serial.println("error");
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

        
         
         
         
}

void reverse(){
         MotorLeft->setSpeed(30);
         MotorLeft->run(BACKWARD); 
         MotorRight->setSpeed(30);
         MotorRight->run(BACKWARD); 
         delay(2000);
         stop_robot();
         
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


 //turn back to 0
void turn_to_zero(){
    float e =-relative_angle(original_angle_compass,compass());
      
     Serial.print("Error");
     Serial.println(e);
      
    while (abs((e)>2))   //while we are over 2 degrees from the angle we want to be at use the proportional control to get there
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
                e =-relative_angle(original_angle_compass,compass());
                
                
         } 
}

void turn(int turn_angle){
    current_angle=relative_angle(original_angle_compass,compass());
    float target_angle = current_angle+turn_angle;
    float e =(target_angle-relative_angle(original_angle_compass,compass()));
    if (e>180){    //correct for when we are at different sides of the compass
      e = e-360;
    }
    if (e<-180){
      e=e+360;
    }
      
      Serial.print("Error");
      Serial.println(e);
      
    while (abs(e)>1)   //while we are over 5 degrees from the angle we want to be at use the proportional control to get there
         {      
                 int M_average = 10;
                 int k_p = 5;
                 Serial.println("error");
                 Serial.println(e);
                 Serial.println("current_angle"); 
                 Serial.println(current_angle); 
                 int p_out = e*k_p;
                 int direction_turn = e/abs(e);
                 int left_motor_out = (M_average +p_out);
                 int right_motor_out = (M_average +p_out);
                 if (right_motor_out>100){
                    right_motor_out=100;
                 }
                 if (left_motor_out>100){
                    left_motor_out=100;
                 }
                 if (direction_turn==1){
                       MotorLeft->run(FORWARD);
                       MotorRight->run(BACKWARD);
                       MotorLeft->setSpeed(left_motor_out); 
                       MotorRight->setSpeed(right_motor_out);
                       Serial.println(left_motor_out);
                       Serial.println(right_motor_out);
                 }
                 else{
                       MotorLeft->run(BACKWARD); 
                       MotorRight->run(FORWARD);
                       MotorLeft->setSpeed(left_motor_out);
                       MotorRight->setSpeed(right_motor_out);
                       Serial.println(left_motor_out);
                       Serial.println(right_motor_out);
                       
                 }
                current_angle = relative_angle(original_angle_compass,compass());
                
                e = (target_angle-current_angle);
                
                
         } 
         
}
         
