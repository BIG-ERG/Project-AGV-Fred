#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

#include "navigatieLogica.h"

void rechtdoor(void){
    //while agv binnen het pad is
    while(distance_right||distance_left>100){
        if(distance_left==distance_right){
            speedStepperLeft(TOPSPEED);
            speedStepperRight(TOPSPEED);
        }
        else{
            if (distance_right < distance_left){
                speedStepperLeft(85);
                speedStepperRight(TOPSPEED);
            }
            if(distance_left< distance_right){
                speedStepperRight(85);
                speedStepperLeft(TOPSPEED);
            }
        }
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
