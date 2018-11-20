
void xycoordinate() 
{     //coordinate finding function
        //get the x coordinate
        // defines ultrasound variables
        long xduration;
        int xdistance;
        long yduration;
        int ydistance;
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
        if (setup_or_loop==0){
          int xcoordinate = xdistance;
          int ycoordinate = ydistance;
          zero[0] = xcoordinate;
          zero[1]=ycoordinate;
          setup_or_loop+=1;
        }
        else{
        int xcoordinate = xdistance-zero[0];
        int ycoordinate = ydistance-zero[1];
        coordinate[0] = xcoordinate ;
        coordinate[1]=ycoordinate;
          
        }
        
       
}
