

  
    
void motor_follow_angle(float current_angle,float desired_angle, int average_speed){

         int M_average = average_speed;   //average speed when following the angle and no adjustment needed
         int k_p=3; //gain for proportional control
         
         
        float e = current_angle-desired_angle; //error from desired angle - if this is positive we are veering to the right and so need to increase right motor and reduce left
        //correct for when we are at different sides of the compass so error is always between 180 and -180
        if (e>180){    
          e = e-360;
        }
        if (e<-180){
          e=e+360;
        }       
         
         p_out = k_p*e;  //output the change in motor needed to correct the angle
         
         int right_motor_out = M_average +p_out;  //set the motor values
         int left_motor_out = M_average -p_out;

         //limit the motors to there maximum output of 255 and 0 so the libary does not get confused
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

         // set the motors to move forward at the required speeds
         MotorRight->run(FORWARD);
         MotorLeft->run(FORWARD);
         MotorLeft->setSpeed(left_motor_out);
          
         MotorRight->setSpeed(right_motor_out);
 }



void reverse(){
  //set the motors to go backwards and reverse for 3 secs
         MotorLeft->setSpeed(100);
         MotorLeft->run(BACKWARD); 
         MotorRight->setSpeed(100);
         MotorRight->run(BACKWARD); 
         delay(3000);
         
         
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
                 //execute turn
                 MotorLeft->setSpeed(left_motor_out);
                 MotorLeft->run(FORWARD); 
                 MotorRight->setSpeed(right_motor_out);
                 MotorRight->run(BACKWARD);
                 delay(turn_time*1000);
                 //stop the motors and reset the current angle for next steps
                 MotorLeft->setSpeed(0);
                 MotorLeft->run(FORWARD); 
                 MotorRight->setSpeed(0);
                 MotorRight->run(FORWARD);
                 delay(2000);
                 current_angle=relative_angle(original_angle_compass,compass());
}




void turn(int turn_angle){
    current_angle=relative_angle(original_angle_compass,compass());
    float target_angle = current_angle+turn_angle;
    float e =(target_angle-relative_angle(original_angle_compass,compass()));
    //correct error so it is always -180 to 180 to fit with the reference frame for angles we are using
    if (e>180){    
      e = e-360;
    }
    if (e<-180){
      e=e+360;
    }
      
     
      
    while (abs(e)>1)   //while we are not within 1 degree of the target angle
         {      
                 int M_average = 10;  //set the average turn speed to be very slow when it approaches the correct angle
                 int k_p = 2;   //gain for proportional control
                 
                 int p_out = e*k_p;  //output for change in motor speed
                 int direction_turn = e/abs(e);    //find the direction we need to turn based on whether the error is positive or negative
                 int left_motor_out = (M_average +p_out);
                 int right_motor_out = (M_average +p_out);

                 //limit the max speed of the motors to 50 so it doesnt spin too fast for the magnometer to keep up
                 if (right_motor_out>50){
                    right_motor_out=50;
                 }
                 if (left_motor_out>50){
                    left_motor_out=50;
                 }

                 //if we need to turn to the right
                 if (direction_turn==1){
                       MotorLeft->run(FORWARD);
                       MotorRight->run(BACKWARD);
                       MotorLeft->setSpeed(left_motor_out); 
                       MotorRight->setSpeed(right_motor_out);
                       Serial.println(left_motor_out);
                       Serial.println(right_motor_out);
                 }
                 //if we need to turn to the left
                 else{
                       MotorLeft->run(BACKWARD); 
                       MotorRight->run(FORWARD);
                       MotorLeft->setSpeed(left_motor_out);
                       MotorRight->setSpeed(right_motor_out);
                       Serial.println(left_motor_out);
                       Serial.println(right_motor_out);
                       
                 }
                //reset the current angle in the current position in turn
                current_angle = relative_angle(original_angle_compass,compass());
                //calculate the current error from the desired angle
                e = (target_angle-current_angle);
                //keep error within 180 to -180
                if (e>180){   
                e = e-360;
              }
              if (e<-180){
                e=e+360;
              }
                
                
         } 
         
}

//ensures we turn the right amount to get to the desired angle
void angle_turn(int desired_angle){   //updates the angle_to_turn global variable
            current_angle=relative_angle(original_angle_compass,compass());
            angle_to_turn = desired_angle-current_angle;
            if (angle_to_turn>180){
              angle_to_turn=angle_to_turn-360;
            }
            if (angle_to_turn<-180){
              angle_to_turn=angle_to_turn+360;
            }
}
