#include <Servo.h>
int servoPin=9;
int servoAngle = -5;
int direction_to_turn = 0;
int i = 0;

const int trigPinx = 10;

const int echoPinx = 11;

//defines zero coordinate and current coordinate
int zero[2];
int coordinate[2];
int setup_or_loop = 0;
void xycoordinate();


void xycoordinate() {     //coordinate finding function
        //get the x coordinate
        // defines ultrasound variables
        long xduration;
        int xdistance;
        
        // Clears the trigPin
        digitalWrite(trigPinx, LOW);
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPinx, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPinx, LOW);
        // Reads the echoPin, returns the sound wave travel time in microseconds
        xduration = pulseIn(echoPinx, HIGH);
        

        // Calculating the distance
        xdistance= xduration*0.034/2;
        //get the y coordinate
        
       
        if (setup_or_loop==0){
          int xcoordinate = xdistance;
          
          zero[0] = xcoordinate;
          
          setup_or_loop+=1;
        }
        else{
        int xcoordinate = xdistance;
        
        coordinate[0] = xcoordinate ;
        
          
        }
        
       
}

Servo servo;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPinx, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPinx, INPUT); // Sets the echoPin as an Input
  servo.attach(servoPin);
  xycoordinate();
  servo.write(servoAngle);
  
}

void loop() {
  // put your main code here, to run repeatedly:
//   i += 1;
//   if (i<38){
//    servoAngle += 5;
//    servo.write(servoAngle);
//    //tale a 
//    xycoordinate();
//    if (coordinate[0]<30){
//      Serial.println("     ");
//      Serial.println(coordinate[0]);
//    }
//    delay(30);
//    
//    
//  }
//  
//  if (i<76 and i>38){
//    servoAngle -= 5;
//    servo.write(servoAngle);
//    xycoordinate();
//        if (coordinate[0]<30){
//      Serial.println("     ");
//      Serial.println(coordinate[0]);
//        }
//    delay(30);  
//    
//  }
//  else if (i>=76){
//    i=0;
//  }
//  
//  
  
}
  
  
