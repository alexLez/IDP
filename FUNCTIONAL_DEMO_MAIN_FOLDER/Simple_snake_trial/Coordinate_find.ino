
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

       
}







void find_coordinate(){
  
  xydistance();
  if (direction_facing == 1){
        xcoordinate = x_length-xdistance;
        ycoordinate = y_length-ydistance;
  }
  else{
        xcoordinate = xdistance;
        ycoordinate = ydistance;
  } 
  
  
  Serial.print(xcoordinate);
  Serial.print(", ");
  Serial.print(ycoordinate);
  
}
