#include "LED.h"

//function to respond to an input of 2 for yellow and 3 for red
void LED(int LED_Colour){
    if (LED_Colour == 2){
    for(int i=1;i<20;i+=1){
    digitalWrite(LED_YELLOW_PIN, HIGH);
    delay(100);
    digitalWrite(LED_YELLOW_PIN, LOW);
    }
  }
  else {
  for(int i=1;i<20;i+=1){
    digitalWrite(LED_RED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_RED_PIN, LOW);
    }
  }
}
