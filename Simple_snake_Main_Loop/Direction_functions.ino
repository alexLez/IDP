


//find angle function

float compass(){
  sensors_event_t event;    //set up event
  mag.getEvent(&event);
  float heading=0;
  for (int i=1;i<10;i+=1){
  heading += atan2(event.magnetic.y+20, event.magnetic.x-9);//get x and y magnetic fields and correct for calbiration (hence the +20 and -9)
  delay(20);
  }
  heading = heading/9;
  float declinationAngle = 0;
  heading += declinationAngle;   //this is based on location and is close to zero for the EITIL
   // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI;
  return headingDegrees;
}


float relative_angle(float original_angle, float current_angle){  //we used a reference frame of 0 when facing forward at start, negative to -180 to left, and positive to +180 to right
  int angle= current_angle-original_angle;
  //correct the angles inputed to our reference frame
  if ((angle)>180){
    angle = angle-360;
  }
  else if ((angle)<-180){
    angle = angle+360;
  }
  return angle;
}
  
