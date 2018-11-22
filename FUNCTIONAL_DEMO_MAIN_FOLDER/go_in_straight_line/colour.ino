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

void rolling_average_reset(){
  for (int i=0;i<10;i+=1){    //fill in the rolling average at the start to get good readings
          rolling_colour[i]=light_levels(Pin1);
          delay(10);
  }
}

void find_current_colour_and_show(int PinA){
  //find the current colour
        for (int i=0;i<9;i+=1){    //all the avlues in array down by one - the most recent level is put at the end
          rolling_colour[i]=rolling_colour[i+1];
        }
        rolling_colour[9] = light_levels(PinA);
        rolling_average = array_average(rolling_colour);//this is the rolling average of the first 8 values so we can compare the final 2 values to check if there is a new colour detected-having 2 values will hopefully remove a little bit of noise  
        BlackRef = rolling_average;  // set the reference level for what we think is normal to be the average levels we are seeing and we move along
        Serial.println("Rolling_average");
        Serial.println(rolling_average);
        if (((rolling_colour[9]+rolling_colour[8])/2)>rolling_average+10  ){    //the 50 is just the minimum that may be a mine as it is a significant jump
             MotorLeft->setSpeed(10);   //slow right down and approach slowly
             MotorLeft->run(FORWARD); 
             MotorRight->setSpeed(10);
             MotorRight->run(FORWARD);
             delay(1000); //delay one second until we are closer in and will hopefully be able to see the full mine
             stop_robot();
             delay(1000); 
             float light_levels_used=light_levels(PinA);  //measure the light levels here
             if (light_levels_used>BlackRef+70){    //this is only for yellow and red at the moment
              colour = 2 ;
              Serial.println("Yellow");//say it is yellow
              Serial.println(analogRead(A0));//print colour value for testing
              digitalWrite(44,HIGH);//flash LED
              delay(10000);
              digitalWrite(44,LOW);
             }
             else if (light_levels_used>BlackRef+20){
              colour = 3;  //say it is red
              
              Serial.println("Red");   //say its red
              Serial.println(analogRead(A0)); //print colour value for testing
              digitalWrite(46,HIGH);  //flash LED
              delay(10000);
              digitalWrite(46,LOW);
              
             }
        }
}
