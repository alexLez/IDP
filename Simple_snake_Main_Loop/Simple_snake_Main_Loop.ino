//include header file for various functions
#include "location.h"
#include "Motor_functions.h"
#include "Direction_functions.h"
#include "mine_detection.h"

//set the length in x and y direction of arena
float y_length=210;
float x_length=210;
 
void setup() {
         Serial.begin(9600);
         
          
         //magnometer set up   
         mag.begin(); //turn the magnometer on
          //set the correct pins as inputs and outputs
         pinMode(trigPinx, OUTPUT); // Sets the trigPin as an Output
         pinMode(echoPinx, INPUT); // Sets the echoPin as an Input
         pinMode(trigPiny, OUTPUT); // Sets the trigPin as an Output
         pinMode(echoPiny, INPUT); // Sets the echoPin as an Input
         pinMode(LED_RED, OUTPUT);   //set the LED pins as outputs
         pinMode(LED_YELLOW, OUTPUT);
         
        
        //read the original magnometer angle here and treat this as 0
        int total_angle_Compass=0  ; //we will take the angle many times and take an average
        for (int i=1; i<=10; i+=1){
          total_angle_Compass+=compass();
          delay(50);
        }
        original_angle_compass = total_angle_Compass/10;

        
        
        
        //set up motors
        
        MotorLeft->run(RELEASE);
        MotorRight->run(RELEASE);
        AFMS.begin();  // create with the default frequency 1.6KHz for motor

        //initilise the colour, current angle,the direction we will be facing, and the angle we will follow at the beginning
        current_angle=relative_angle(original_angle_compass,compass());
        angle_to_follow=current_angle;
        colour=0;
        direction_facing=1;
        //execute a starting routine to avoid the white lines in the starting box

        //move forward for 7 secs to get out of the box
        MotorRight->run(FORWARD);
        MotorLeft->run(FORWARD);
        MotorLeft->setSpeed(30);
        MotorRight->setSpeed(30);
        delay(7000);

        //turn 90 degress to left and move for 3 secs to get away from the white lines on the right of the robot
        turn(-90);
        stop_robot();
        delay(1000);

        //drive forward for 3 secs
        current_angle=relative_angle(original_angle_compass,compass());
        angle_to_follow=-90;
        for (int i=1;i<=150;i++){
        motor_follow_angle(current_angle,-90,100);
        delay(20);
        }
        
        stop_robot();
        delay(1000);
        //turn back to 0
        turn(90);
        angle_to_follow=0;
        stop_robot();
        delay(1000);

        //ceck the current angle and turn a little bit more to ensure we are at an angle of 0 degrees 
        current_angle=relative_angle(original_angle_compass,compass());
        turn(-current_angle);
        stop_robot();
        delay(1000);
        
        //set the rolling average for the colour when we are over the black
        initial_rolling_average_reset();
}



 



void loop() {
        //get data

        //get the current angle and make it relative to the original angle on a -180 to 180 scale
        current_angle=relative_angle(original_angle_compass,compass());
        
        //set the motors to follow the desired angle angle
        motor_follow_angle(current_angle, angle_to_follow,100); 

        //find the current colour in front and set the colour variable appropriately
        find_current_colour_and_show(10,20,100,5,10,100,10,20,100);
        
        //find the distances from the wall
        xydistance();
        
        //check the distance from the wall and act accordingly
        if ((y_length-ydistance)<=20){
          delay(2000);
          stop_robot();
          if (direction_facing==-1){   //if facing in opposite direction to before
            //reverse for a couple of secs to leave any collected mines outside safe zone
            reverse();
            //stop and turn 90 degrees to right
            stop_robot();
            angle_turn(-90);   //find angle that will make robot facing in -90 direction
            turn(angle_to_turn);
            stop_robot();
            delay(1000);
            
            //move forward for 4 seconds to snake
            for (int i=1;i<=20;i++){
            current_angle=relative_angle(original_angle_compass,compass());
            motor_follow_angle(current_angle,-90,30);
            delay(200);
            }
            
            stop_robot();
            delay(1000);

            //stop and turn 90 degrees right to get back to 0 
            angle_turn(0); //find angle that will make robot facing in -90 direction
            turn(angle_to_turn);
            delay(2000);
            current_angle=relative_angle(original_angle_compass,compass());
            //reset angle to follow as 0 and go strsight and return to snake
            angle_to_follow=0;
            motor_follow_angle(current_angle,angle_to_follow,100);
            
            //set direction so we are now going in the other direction to the original direction
            direction_facing=1; 
          }

          //do the same as above but as though facing in the other direction
          else{
            
            reverse();
            
            stop_robot();//reverse for a couple of secs to leave any collected mines outside then stop and turn
            angle_turn(-90); //find angle that will make robot facing in -90 direction
            turn(angle_to_turn);
            stop_robot();
            delay(1000);

            //move straight for 2 secs
            for (int i=1;i<=10;i++){
            current_angle=relative_angle(original_angle_compass,compass());
            motor_follow_angle(current_angle,-90,100);
            delay(200);
            }
            stop_robot();
            delay(1000);
            //turn  to 180 degrees direction
            angle_turn(180); //find angle that will make robot facing in 180 direction
            turn(angle_to_turn);
            delay(2000);
            current_angle=relative_angle(original_angle_compass,compass());
            angle_to_follow=180;
            motor_follow_angle(current_angle,angle_to_follow,100);
            
            direction_facing=-1; //set it so we are now going in the other direction to the original direction
          }
          
        }


        //colour checks
        
        if (colour==0){  //if the colour is black
           // servo angle+=5;
            //pass and keep going as we are
        }

       else if (colour==2){   //yellow
              //turn into the zone we have already checked, and drop the yellow mine off at the side
              int store_angle_to_follow=angle_to_follow;  //remember the angle we are currently following

              //move forward for 2 secs to make sure mine is at the back and won't fall out
              for(int i=1;i<=10;i++){
              motor_follow_angle(current_angle,current_angle,50);
              delay(200);
              }
              
              stop_robot();
              //turn to face the -90 degree direction
              current_angle=relative_angle(original_angle_compass,compass());
              angle_to_follow=current_angle;
              angle_turn(-90);
              turn(angle_to_turn);

              //measure current position in the x direction and store it (y distance as the robot has rotated so using the y ultrasound sensor
              xydistance();
              current_position=y_length-ydistance;

              //move forward until we are around 20 cm from the wall
              while (x_length-ydistance<=20){
                motor_follow_angle(current_angle,-90,50);
                xydistance; //keep updating ydistance
                delay(200);
              }
              //stop and then move back to leave the mine behind
              stop_robot();
              reverse();
              delay(1000); //add an extra second to reverse move to ensure we are well away from mine
              stop_robot();
              //turn 180 degrees to head back
              angle_turn(90); //we need to face in 90 degrees direction
              turn(angle_to_turn);

              //move forward until we get to the same position as before
              while (ydistance<=current_position){
                motor_follow_angle(current_angle,90,50);
                xydistance; //keep updating ydistance
                delay(200);
              }
              stop_robot();

              //turn back to face original direction we were following
              angle_turn(store_angle_to_follow); //we need to face in 90 degrees direction
              turn(angle_to_turn);
              stop_robot();
              
              //reset so robot is same as before find yellow mine, and carry on
              
              
             angle_to_follow=store_angle_to_follow;
       }
       else if (colour==3){//red
               //we are currently stationary so reverse for 4 secs to get away
             MotorLeft->setSpeed(50);   
             MotorLeft->run(BACKWARD); 
             MotorRight->setSpeed(50);
             MotorRight->run(BACKWARD); 
             delay(4000);
             stop_robot();
             delay(1000);
             find_coordinate();  //find and record the current coordinates
             
             //go around the red mine to the left where we know it is safe if we are going up, and to the right if we are going down
             if (direction_facing==1){
                     turn(45);
                     stop_robot();
                     //go straight for 3 secs
                     for (int i=1;i<=150;i++){
                    current_angle=relative_angle(original_angle_compass,compass());
                    motor_follow_angle(current_angle,45,100);
                    delay(20);
                    }
                     stop_robot();
                     delay(1000);
                     turn(-90);
                     stop_robot();
                     //go straight for 3 secs to back to same point
                     for (int i=1;i<=150;i++){
                    current_angle=relative_angle(original_angle_compass,compass());
                    motor_follow_angle(current_angle,-45,100);
                    delay(20);
                    }
                     angle_turn(0);//return to facing the 0 direction again
                     turn(angle_to_turn);
                     current_angle=relative_angle(original_angle_compass,compass());
                     motor_follow_angle(current_angle,0,100);
                     angle_to_follow=0;
                     }
             else {
                  turn(-45);
                 stop_robot();
                 //go straight for 3 secs
                 for (int i=1;i<=15;i++){
                current_angle=relative_angle(original_angle_compass,compass());
                motor_follow_angle(current_angle,135,100);
                delay(20);
                }
                 stop_robot();
                 delay(1000);
                 turn(90);
                 stop_robot();
                 //go straight for 3 secs
                 for (int i=1;i<=15;i++){
                 current_angle=relative_angle(original_angle_compass,compass());
                 motor_follow_angle(current_angle,-135,100);
                 delay(20);
                 }
                 angle_turn(180);  //return to facing 1 180 degrees direction and continue moving 
                 turn(angle_to_turn);
                 current_angle=relative_angle(original_angle_compass,compass());
                 motor_follow_angle(current_angle,180,100);
                 angle_to_follow=180;
             }
             
           
                  
       }
       colour=0;//reset it to black once manouver has been completed  
       
      
      
        }
          
        
        
          
        
        
        
  
