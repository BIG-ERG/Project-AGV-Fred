#include <avr/io.h>
#include <math.h>

#include "navigatieLogica.h"
#include "ultrasoon.h"
#include "stepperDriver.h"

void rechtdoor(void){
    //start driving
    speedStepperLeft(TOPSPEED);
    speedStepperRight(TOPSPEED);
    //while agv binnen het pad is
    while(distance_right||distance_left<50){
        //bepaal ratio van afwijking en gebruik deze om de snelheid aan te passen
        if (distance_right < distance_left)
            speedStepperLeft(TOPSPEED*(distance_right/distance_left));
        else
            speedStepperRight(TOPSPEED*(distance_left/distance_right));
    }
    //stop driving
    speedStepperLeft(0);
    speedStepperRight(0);
}

void rechtsom(void){
    double stepsOuter = ((((distance_left + breedteAGV + afstandWielAgv)*M_PI)/omtrekWiel)*360)/STEPANGLE;
    double stepsInner = ((((distance_right - afstandWielAgv)*M_PI)/omtrekWiel)*360)/STEPANGLE;
    double stepRatio = stepsOuter/stepsInner;

    //clear stepcounter
    stepCounterLeft=0;
    //start turning
    while(stepCounterLeft<stepsOuter){
        speedStepperLeft(TOPSPEED);
        speedStepperRight(TOPSPEED*stepRatio);
    }
    //stop turning
    speedStepperLeft(0);
    speedStepperRight(0);
}

/*
stepper driver
void initPinsStepper (void);
void initTimer1Stepper(void);
void initStepper(void);

void speedStepperRight(int PWMRight);
void speedStepperLeft(int PWMLeft);


void toggledirectionStepperLeft(void);
void toggledirectionStepperRight(void);


ultrasoon
volatile int distance_right;
volatile int distance_left;
*/
