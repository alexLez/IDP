int sensorPin = A0;    // select the input pin for the potentiometer

int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);           //Start serial and set the correct Baud Rate
  //yellow led
  pinMode(52, OUTPUT);
  //red led
  pinMode(53, OUTPUT);
}

//declare initial values for colours
int white = 0;
int yellow = 0;
int red = 0;
int black = 550;


void loop() {
  sensorValue = analogRead(sensorPin);
  if (sensorValue < black)
  {
    if (sensorValue > black-50) //don't take sudden drops into account
    {black = sensorValue;}
  }
  yellow = black + 200;
  red = black + 100;
  //white = black + 30; -> will probably use blue LED, not certain
  digitalWrite(52,LOW);
  digitalWrite(53,LOW);
  if (sensorValue >= red)
  {
    if (sensorValue < yellow)
    {//the colour identified is red 
    digitalWrite(53,HIGH);}
    else 
    //{
     // if (sensorValue < yellow) {//Serial.println("White");
       // }
      //else
      {//the colour identified is yellow
      digitalWrite(52,HIGH);}
    }
  Serial.println(sensorValue);
}
