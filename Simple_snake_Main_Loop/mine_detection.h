int light_levels(int pin,int LDR);
void rolling_average_reset();
void find_current_colour_and_show(int something1,int red1, int yellow1,int something2,int red2, int yellow2,int something3,int red3, int yellow3);
void initial_rolling_average_reset();
float array_average(float array1[10]);

//define the global variables needed for colour functions
//varialbe to hold colurs
int colour=0;

//pins for LDR circuit inputs
int Pin1=A10;
int Pin2 =A9;
int Pin3=A8;
float BlackRef1;
float BlackRef2;
float BlackRef3;
float rolling_colour1[10]={0,0,0,0,0,0,0,0,0,0};  //create a colour array full of zeros
float rolling_colour2[10]={0,0,0,0,0,0,0,0,0,0};  //create a colour array full of zeros
float rolling_colour3[10]={0,0,0,0,0,0,0,0,0,0};  //create a colour array full of zeros
float rolling_average1;
float rolling_average2;
float rolling_average3;
float instantaneous_reading_average1;
float instantaneous_reading_average2;
float instantaneous_reading_average3;

//define the LED pins
int LED_YELLOW=52;
int LED_RED=53;
