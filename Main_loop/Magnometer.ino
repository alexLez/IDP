


//find angle function

float compass(){
  sensors_event_t event;    //set up event
  mag.getEvent(&event);
  float heading = atan2(event.magnetic.y, event.magnetic.x);    //get x and y magnetic fields
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
