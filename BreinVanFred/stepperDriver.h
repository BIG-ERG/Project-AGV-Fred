#ifndef STEPPERDRIVER_H_INCLUDED
#define STEPPERDRIVER_H_INCLUDED

#define TOPVALUE 1
#define STEPPER_LEFT PB5
#define STEPPER_RIGHT PB6
#define DDR_STEP_R  DDRB
#define PORT_STEP_R PORTB
#define DDR_STEP_L  DDRB
#define PORT_STEP_L PORTB

void initPinsStepper (void);
void initTimer1Stepper(void);
void initStepper(void);

void speedStepperRight(int PWMRight);
void speedStepperLeft(int PWMLeft);

#endif // STEPPERDRIVER_H_INCLUDED
