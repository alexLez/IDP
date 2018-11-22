#include "colour.h"



int light_levels(int pin){    //return an integer representing the colour that is present
  //create a running total so we can find an average and remove anomalies
  int light_intensity_levels_sum=0;
  for (int i=1;i<=10;i+=1){
    light_intensity_levels_sum+= analogRead(Pin1);
    delay(10);
  }
  int average =light_intensity_levels_sum/10    ;         



  return average;
}

float array_average(float array1[10]){
  float total = 0;
  for (int i=0;i<8;i+=1){
    total+=array1[i];
  }
  float average = total/8;
  return average;
}
