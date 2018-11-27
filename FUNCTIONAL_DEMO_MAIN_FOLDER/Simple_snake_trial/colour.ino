#include "colour.h"



int light_levels(int pin,int LDR){    //return an integer representing the colour that is present
  //create a running total so we can find an average and remove anomalies
  int light_intensity_levels_sum=0;
  for (int i=0;i<=9;i++){
    light_intensity_levels_sum+= analogRead(pin);
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

void rolling_average_reset(){
  for (int i=0;i<10;i+=1){    //fill in the rolling average at the start to get good readings
          rolling_colour1[i]=light_levels(Pin1,1);
          delay(10);
      }
  for (int i=0;i<10;i+=1){    //fill in the rolling average at the start to get good readings
          rolling_colour2[i]=light_levels(Pin2,2);
          delay(10);
  }
  for (int i=0;i<10;i+=1){    //fill in the rolling average at the start to get good readings
          rolling_colour3[i]=light_levels(Pin3,3);
          delay(10);
  }
}

void find_current_colour_and_show(int something,int red, int yellow){
  //find the current colour
        for (int i=0;i<9;i+=1){    //all the avlues in array down by one - the most recent level is put at the end
          rolling_colour1[i]=rolling_colour1[i+1];
          rolling_colour2[i]=rolling_colour2[i+1];
          rolling_colour3[i]=rolling_colour3[i+1];
        }
        rolling_colour1[9] = light_levels(Pin1,1);
        rolling_colour2[9] = light_levels(Pin2,2);
        rolling_colour3[9] = light_levels(Pin3,3);
        rolling_average1 = array_average(rolling_colour1);//this is the rolling average of the first 8 values so we can compare the final 2 values to check if there is a new colour detected-having 2 values will hopefully remove a little bit of noise 
        rolling_average2 = array_average(rolling_colour2);
        rolling_average3 = array_average(rolling_colour3); 
        BlackRef1 = rolling_average1;  // set the reference level for what we think is normal to be the average levels we are seeing and we move along
        BlackRef2 = rolling_average2;
        BlackRef3 = rolling_average3;
        Serial.println("Rolling_average1");
        Serial.println(rolling_average1);
        instantaneous_reading_average1 = ((rolling_colour1[9]+rolling_colour1[8])/2);
        instantaneous_reading_average2 = ((rolling_colour2[9]+rolling_colour2[8])/2);
        instantaneous_reading_average3 = ((rolling_colour3[9]+rolling_colour3[8])/2);
        if ((instantaneous_reading_average1>rolling_average1+something) or (instantaneous_reading_average2>rolling_average2+something) or (instantaneous_reading_average3>rolling_average3+something)){//if there is anything detected, slow down and check it  ){  //if the sensor readings for any of the LDRs jumps up, slow down and approach
             MotorLeft->setSpeed(10);   //slow right down and approach slowly
             MotorLeft->run(FORWARD); 
             MotorRight->setSpeed(10);
             MotorRight->run(FORWARD);
             delay(1000); //delay one second until we are closer in and will hopefully be able to see the full mine
             stop_robot();
             delay(1000); 
             float light_levels_used1=light_levels(Pin1,1);  //measure the light levels here for sensor 1
             float light_levels_used2=light_levels(Pin2,2);  //measure the light levels here for sensor 2
             float light_levels_used3=light_levels(Pin3,3);  //measure the light levels here for sensor 3
             if ((light_levels_used1>BlackRef1+yellow)or (light_levels_used2>BlackRef2+yellow) or (light_levels_used3>BlackRef3+yellow)){    //if any of them are yellow we say it is yellow
              colour = 2 ;
              Serial.println("Yellow");//say it is yellow
              Serial.println(analogRead(A0));//print colour value for testing
              digitalWrite(44,HIGH);//flash LED
              delay(3000);
              digitalWrite(44,LOW);
             }
             else if ((light_levels_used2>BlackRef2+red) or (light_levels_used1>BlackRef1+red) or (light_levels_used3>BlackRef3+red)){   //red if any of them are red
              colour = 3;  //say it is red
              
              Serial.println("Red");   //say its red
              Serial.println(analogRead(A0)); //print colour value for testing
              digitalWrite(46,HIGH);  //flash LED
              delay(3000);
              digitalWrite(46,LOW);
              
             }
        }
}
