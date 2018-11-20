#include "colours.h"

int colour_present(){    //return an integer representing the colour that is present
  //fill in an array with 10 readings over the course of 0.1 secs
  int light_intensity_levels[10];
  //create a running total so we can find an average and remove anomalies
  int light_intensity_levels_sum=0;
  for (int i=1,i<=10,i+=1){
    light_intensity_levels[i]=analogRead(Pin1);
    light_intensity_levels_sum+= analogRead(Pin1);
  }
  int average =light_intensity_levels_sum/10                   //made a start, not sure how you will want to procede
}
