

  
    
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

void decide_where_to_turn_and_turn(){
            if (ydistance>40 and xdistance>(x_length-70)){   //on left hand side in the middle area
             rand_turn_time = random(0.4,2.7);//turn right between 10 and 170 ;
             turn_no_compass(rand_turn_time,1,255);
             }
             else if (ydistance<=40 and xdistance>(x_length-70) ){  //top left
             rand_turn_time = random(1.6,2.7);//turn right between 100 and 170 ;
             turn_no_compass(rand_turn_time,1,255);
             }
             else if (ydistance>40 and xdistance<=(x_length-70)){   //on right hand side in the middle area
             rand_turn_time = random(0.4,2.7);//turn left between 10 and 170 ;
             turn_no_compass(rand_turn_time,-1,255);
             }
             else if (ydistance<=40 and xdistance<=(x_length-70) ){  //top right
             rand_turn_time = random(1.6,2.7);//turn left between 100 and 170 ;
             turn_no_compass(rand_turn_time,-1,255);
             }
             else if (y_length-ydistance<=40 and xdistance>(x_length-70) ){  //bottom left
             rand_turn_time = random(0.4,1.4);//turn right between 10 and 80 ;
             turn_no_compass(rand_turn_time,1,255);
             }
             else if (y_length-ydistance<=40 and xdistance<(x_length-70) ){  //bottom right
             rand_turn_time = random(0.4,1.4);//turn left between 10 and 80 ;
             turn_no_compass(rand_turn_time,-1,255);
             }
  
}
         
