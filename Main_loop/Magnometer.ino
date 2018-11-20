

//find angle function

float compass(){
  sensors_event_t event;    //set up event
  mag.getEvent(&event);
  float heading=0;
  for (int i=1;i<20;i+=1){
  heading += atan2(event.magnetic.y, event.magnetic.x);    //get x and y magnetic fields
  delay(10);
  }
  heading = heading/19;
  float declinationAngle = 0;
  heading += declinationAngle;   //this is based on location
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

float relative_angle(float original_angle, float current_angle){
  int angle= current_angle-original_angle;
  if ((angle)>180){
    angle = angle-360;
  }
  else if ((angle)<-180){
    angle = angle+360;
  }
  return angle;
}
