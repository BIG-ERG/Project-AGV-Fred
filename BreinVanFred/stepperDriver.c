/*
step instelling: sixteen steps (MS1 hoog, MS2 hoog, MS3 hoog)
stepper right: digital pin 11
stepper left: digital pin 12
voorlopig geen enable/disable pin voor driver board

f = 400 Hz -> T = 0.0025 s -> 0.0025*16000000 = 40000 cycles
Prescaler: 16000000/40000 = 0.61 -> 1 -> CS = 0b001
Top-value: 16000000/256 = 62500
OCRA value: 1*1 = 1
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "stepperDriver.h"

void initPinsStepper (void){
	// Config pins as output
	DDR_STEP_R |= (1<<STEPPER_RIGHT);
	DDR_STEP_L |= (1<<STEPPER_LEFT);

	// Output low
	PORT_STEP_R &= ~(1<<STEPPER_RIGHT);
	PORT_STEP_L &= ~(1<<STEPPER_LEFT);
}

void initTimer1Stepper(void){
    // Use mode 14, clkdiv = 1
    TCCR1A = (1<<WGM11) | (0<<WGM10) | (1<<COM1A1) | (1<<COM1A0) | (1<<COM1B0) | (1<<COM1B1);
    TCCR1B = (1<<WGM13) | (1<<WGM12) | (0<<CS12) | (0<<CS11) | (1<<CS10);

	//define top value
	ICR1 = TOPVALUE;
}

void initStepper(void){
    initTimer1Stepper();
    initPinsStepper();
}

void speedStepperRight(int PWMRight){
    OCR1A = PWMRight;
}

void speedStepperLeft(int PWMLeft){
    OCR1B = PWMLeft;
}
