
void xydistance() {     //coordinate finding function
        //get the x coordinate
        // defines ultrasound variables
        long xduration;
        
        long yduration;
        
        // Clears the trigPin
        digitalWrite(trigPinx, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPinx, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPinx, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        xduration = pulseIn(echoPinx, HIGH);
        // Calculating the distance
        xdistance= xduration*0.034/2;
        //get the y coordinate
        
        // Clears the trigPin
        digitalWrite(trigPiny, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPiny, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPiny, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        yduration = pulseIn(echoPiny, HIGH);
        // Calculating the distance
        ydistance= yduration*0.034/2;
//        if (setup_or_loop==0){
//          int xcoordinate = xdistance;
//          int ycoordinate = ydistance;
//          zero[0] = xcoordinate;
//          zero[1]=ycoordinate;
//          setup_or_loop+=1;
//        }
//        else{
//        int xcoordinate = xdistance-zero[0];
//        int ycoordinate = ydistance-zero[1];
//        coordinate[0] = xcoordinate ;
//        coordinate[1]=ycoordinate;
          
        //}
        
       
}





void servo_ultrasound(){
  ultrasound_turner.write(servo_angle);
  xydistance();
  if (xdistance or ydistance) < 20 and (xdistance or ydistance) > 10 {
    count ++;
  }
  if (servo_angle >=180){
    forward_sweep = false;
    if (count >= 3){
      reverse();
      rand_turn_time = random(1.5,4.5);
      turn_no_compass(rand_turn_time,-1,255);
      wall = true;
    }
    count = 0;
  }
  if (servo_angle <= 0){
    forward_sweep = true;
    if (count >= 3){
      reverse();
      rand_turn_time = random(1.5,4.5);
      turn_no_compass(rand_turn_time,-1,255);
      wall = true;
    }
    count = 0;
  }
  if (forward_sweep){
    servo_angle+=5 ;
  }
  else{
    servo_angle-=5;     
  }

}
