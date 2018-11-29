



int light_levels(int pin,int LDR){    //return an integer representing the average light level that is instantaneously detected
  //create a running total so we can find an average and remove anomalies
  int light_intensity_levels_sum=0;
  //record the light levels 10 times and take an average
  for (int i=0;i<=9;i++){
    light_intensity_levels_sum+= analogRead(pin);
    delay(10);
   }
  
  int average =light_intensity_levels_sum/10    ;         



  return average;
}


float array_average(float array1[10]){ //find the average of the rolling average array containing the 10 most recent readings
  float total = 0;
  for (int i=0;i<8;i+=1){
    total+=array1[i];
  }
  float average = total/8;
  return average;
}

 void rolling_average_reset(){  //reset the rolling average, used after we have detected mines so the high readings don't skew the results
 //fill in the rolling average arrays for all 3 LDRs
  
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
void initial_rolling_average_reset(){   //fill in the rolling average twice at the start as the LDRs often give bad readings when first used so this hopefully eliminates that
  
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
  for (int i=0;i<10;i+=1){    //fill in the rolling average at the start to get good readings
          rolling_colour1[i]=light_levels(Pin1,1);
          delay(20);
      }
  for (int i=0;i<10;i+=1){    //fill in the rolling average at the start to get good readings
          rolling_colour2[i]=light_levels(Pin2,2);
          delay(20);
  }
  for (int i=0;i<10;i+=1){    //fill in the rolling average at the start to get good readings
          rolling_colour3[i]=light_levels(Pin3,3);
          delay(20);
  }
}


void find_current_colour_and_show(int something1,int red1, int yellow1,int something2,int red2, int yellow2,int something3,int red3, int yellow3){  //set the thresholds for when we thing 'something' is there, and then when there is red or yellow there
  //find the current colour
        for (int i=0;i<9;i+=1){    //shift all the values in rolling average array down by one - the most recent reading is put at the end
          rolling_colour1[i]=rolling_colour1[i+1];
          rolling_colour2[i]=rolling_colour2[i+1];
          rolling_colour3[i]=rolling_colour3[i+1];
        }

        //fill in the array with the most recent reading
        rolling_colour1[9] = light_levels(Pin1,1);
        rolling_colour2[9] = light_levels(Pin2,2);
        rolling_colour3[9] = light_levels(Pin3,3);
        
        //caclualte the rolling average of the first 8 readings, not including the 2 most recent so we can detect changes
        rolling_average1 = array_average(rolling_colour1); 
        rolling_average2 = array_average(rolling_colour2);
        rolling_average3 = array_average(rolling_colour3); 
        
        // set the reference level for what we think is normal to be the average levels we are seeing as we move along - this is hopefully the black levels
        BlackRef1 = rolling_average1;  
        BlackRef2 = rolling_average2;
        BlackRef3 = rolling_average3;

        //calcualte the average of the last 2 readings so the most recent colours we have seen to possibly detect spikes
        instantaneous_reading_average1 = ((rolling_colour1[9]+rolling_colour1[8])/2);
        instantaneous_reading_average2 = ((rolling_colour2[9]+rolling_colour2[8])/2);
        instantaneous_reading_average3 = ((rolling_colour3[9]+rolling_colour3[8])/2);
        
        //if the sensor readings for any of the LDRs jumps up, slow down and approach
        if ((instantaneous_reading_average1>rolling_average1+something1) or (instantaneous_reading_average2>rolling_average2+something2) or (instantaneous_reading_average3>rolling_average3+something3)){
             
             MotorLeft->setSpeed(10);   //slow right down and approach slowly
             MotorLeft->run(FORWARD); 
             MotorRight->setSpeed(10);
             MotorRight->run(FORWARD);
             delay(1000); //delay one second until we are closer in and will hopefully be able to see the full mine
             stop_robot();
             //stop and now measure the light levels that we will use
             float light_levels_used1=light_levels(Pin1,1);  //measure the light levels here for sensor 1
             float light_levels_used2=light_levels(Pin2,2);  //measure the light levels here for sensor 2
             float light_levels_used3=light_levels(Pin3,3);  //measure the light levels here for sensor 3

             //compare light levels with the black reference and if any of them are yellow, declare it as yellow
             
             if ((light_levels_used1>BlackRef1+yellow1)or (light_levels_used2>BlackRef2+yellow2) or (light_levels_used3>BlackRef3+yellow3)){    //if any of them are yellow we say it is yellow
              colour = 2 ;// colour is set to 2 so for the rest of the loop we know what colour is present
             
              digitalWrite(52,HIGH);//flash LED
              delay(3000);
              digitalWrite(52,LOW);
             }
             //if non were yellow, check if any are red
             else if ((light_levels_used2>BlackRef2+red2) or (light_levels_used1>BlackRef1+red1) or (light_levels_used3>BlackRef3+red3)){   //red if any of them are red
              colour = 3;  //say it is red by setting colour to 3 so rest of loop acts appropriately
     
              digitalWrite(53,HIGH);  //flash LED
              delay(3000);
              digitalWrite(53,LOW);
              
             }
             
        }
}
