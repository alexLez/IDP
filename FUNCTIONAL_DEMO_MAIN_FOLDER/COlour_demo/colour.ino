#include "colour.h"


//PROBS WONT NEED THIS BIT

//int Find_Black_Ref(){                   //run this at the start to determine a value for the black one
//  int light_intensity_levels[10];
//  //create a running total so we can find an average and remove anomalies
//  int light_intensity_levels_sum=0;
//  for (int i=1,i<=10,i+=1){
//    light_intensity_levels[i]=analogRead(Pin1);
//    light_intensity_levels_sum+= analogRead(Pin1);
//  }
//  int average =light_intensity_levels_sum/10    
//  return average
//   
//}

int light_levels(int pin){    //return an integer representing the colour that is present
  //create a running total so we can find an average and remove anomalies
  int light_intensity_levels_sum=0;
  for (int i=1;i<=10;i+=1){
    light_intensity_levels_sum+= analogRead(Pin1);
    delay(1);
  }
  int average =light_intensity_levels_sum/10    ;         



  return average;
}

float array_average(float array1[10]){
  float total = 0;
  for (int i=0;i<10;i+=1){
    total+=array1[i];
  }
  float average = total/10;
  return average;
}
