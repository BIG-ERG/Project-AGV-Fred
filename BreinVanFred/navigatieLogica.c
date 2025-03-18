#include <avr/io.h>

#include "navigatieLogica.h"
#include "ultrasoon.h"
#include "stepperDriver.h"

void rechtdoor(void){
    //ratio bepaald welke motor langzamer moet draaien relatief aan de ander om centraal te staan aan de route
    int ratio;
    if (distance_right < distance_left)
        ratio = distance_right / distance_left;
    else
        ratio = distance_left / distance_right;
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
