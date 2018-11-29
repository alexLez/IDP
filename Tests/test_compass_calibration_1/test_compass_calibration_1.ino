/*
 * motorTest.h
 *
 *  Created on: 20 Nov 2018
 *      Author: lewis
 *
 *  Gets data for compass calibration
 */

#include "libraries.h"
using namespace std;
// Assign compass to compass object
Adafruit_HMC5883_Unified calibrationCompass = Adafruit_HMC5883_Unified();

// Assigns motors to motor objects

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *MotorLeft = AFMS.getMotor(2);
Adafruit_DCMotor *MotorRight = AFMS.getMotor(1);
// Initialise counter variable
int runCounter = 0;

// Initialise flux variables
float currentYFlux;
float currentXFlux;


// Initialise superlative flux variables
float maxYFlux = .0;
float maxXFlux = .0;
float minYFlux = .0;
float minXFlux = .0;

// Initialise results vectors
vector<float> yFluxes;
vector<float> xFluxes;

void setup () {
    //Start serial transmission
    Serial.begin(9600);

    //Start compass
    calibrationCompass.begin();
    Serial.println("Set-up Complete!");

    // Initialise motor shield
    AFMS.begin();
    MotorLeft.assignedMotorShield = motorShield;
    MotorRight.assignedMotorShield = motorShield;
    MotorLeft.init();
    MotorRight.init();
}

void loop() {
    if (runCounter < 600) {
        MotorLeft.setSpeed(225);
        MotorRight.setSpeed(225);
        MotorLeft.setForward();
        MotorRight.setBackward();
        
        // Fetch current compass flux readings
        sensors_event_t reading;
        calibrationCompass.getEvent(&reading);

        // Assign flux readings to variables
        currentYFlux = reading.magnetic.y;
        currentXFlux = reading.magnetic.x;
        
        // Print current fluxes to serial
        Serial.print(currentXFlux);
        Serial.print(",");
        Serial.println(currentYFlux);

        // Increment runCounter
        runCounter += 1;

        delay(100);
    }
    else{
        MotorLeft.emergencyStop();
        MotorRight.emergencyStop();
        /*
        Serial.print("Max Y Flux: ");
        Serial.println(maxYFlux);
        Serial.print("Min Y Flux: ");
        Serial.println(minYFlux);
        Serial.print("Max X Flux: ");
        Serial.println(maxXFlux);
        Serial.print("Min X Flux: ");
        Serial.println(minXFlux);
        Serial.print("X Offset: ");
        Serial.println((minXFlux + maxXFlux)/2);
        Serial.print("Y Offset: ");
        Serial.println((minYFlux + maxYFlux)/2);*/
    }
}
