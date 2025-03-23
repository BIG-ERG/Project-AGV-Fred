/*
step instelling: sixteen steps (MS1 hoog, MS2 hoog, MS3 hoog)
stepper right: digital pin 11
voorlopig geen enable/disable pin voor driver board
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "stepperDriver.h"

void initPinsStepper (void){
	// Config pins as output
	DDR_STEP_R |= (1<<STEPPER_RIGHT);
	DDR_STEP_L |= (1<<STEPPER_LEFT);
	DDR_DIR_R |= (1<<PORT_DIR_R);
	DDR_DIR_L |= (1<<PORT_DIR_L);

	// Output low
	PORT_STEP_R &= ~(1<<STEPPER_RIGHT);
	PORT_STEP_L &= ~(1<<STEPPER_LEFT);
	PORT_DIR_L &= ~(1<<DIRECTION_L);
	PORT_DIR_R &= ~(1<<DIRECTION_R);
}

//stepper right
void initTimer3Stepper(void){
    // Use mode 14, prescaler = 256
    TCCR3A = (1<<WGM31) | (0<<WGM30) | (1<<COM3A1) | (1<<COM3A0);
    TCCR3B = (1<<WGM33) | (1<<WGM32) | (1<<CS32) | (0<<CS31) | (0<<CS30);

    //interrupt on inputcapture
    TIMSK3 = (1<<ICIE3);

	//define step value
    OCR3A = STEPVALUE;
}

//stepper left
void initTimer4Stepper(void){
    // Use mode 14, prescaler = 256
    TCCR4A = (1<<WGM41) | (0<<WGM40) | (1<<COM4A1) | (1<<COM4A0);
    TCCR4B = (1<<WGM43) | (1<<WGM42) | (1<<CS42) | (0<<CS41) | (0<<CS40);

    //interrupt on inputcapture
    TIMSK4 = (1<<ICIE4);

	//define step value
    OCR4A = STEPVALUE;
}


void initStepper(void){
    initTimer4Stepper();
    initTimer3Stepper();
    initPinsStepper();
}

void speedStepperRight(int PWMRight){
    ICR3 = PWMRight;
}

void speedStepperLeft(int PWMLeft){
    ICR4 = PWMLeft;
}

void toggleStepperDirectionRight(void){
    PORT_DIR_R ^= ~(1<<DIRECTION_R);
}

void toggleStepperDirectionLeft(void){
    PORT_DIR_L ^= (1<<DIRECTION_L);
}

volatile unsigned int stepCounterLeft = 0;
ISR(TIMER4_OVF_vect){
    stepCounterLeft++;
}

volatile unsigned int stepCounterRight = 0;
ISR(TIMER3_OVF_vect){
    stepCounterRight++;
}
