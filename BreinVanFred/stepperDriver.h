#ifndef STEPPER_DRIVER_H_INCLUDED
#define STEPPER_DRIVER_H_INCLUDED

#define STEPVALUE 1 //16us

#define STEPPER_RIGHT PE3
#define DDR_STEP_R  DDRE
#define PORT_STEP_R PORTE
#define DDR_DIR_R DDRG
#define PORT_DIR_R PG4

#define STEPPER_LEFT PH3
#define DDR_STEP_L  DDRH
#define PORT_STEP_L PORTH
#define DDR_DIR_L DDRH
#define PORT_DIR_L PH4

void initPinsStepper (void);
void initTimer1Stepper(void);
void initTimer4Stepper(void);
void initStepper(void);

void speedStepperRight(int PWMRight);
void speedStepperLeft(int PWMLeft);

void toggleStepperDirectionRight(void);
void toggleStepperDirectionLeft(void);

#endif // STEPPER_DRIVER_H_INCLUDED
