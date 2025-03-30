#ifndef STEPPER_DRIVER_H_INCLUDED
#define STEPPER_DRIVER_H_INCLUDED

#define STEPVALUE 1 //16us

#define STEPANGLE 5.6
#define omtrekWiel  188.5  //D*pi
#define breedteAGV 134
#define afstandWielAgv 13 //mm

#define STEPPER_RIGHT PE3
#define DDR_STEP_R  DDRE
#define PORT_STEP_R PORTE
#define DDR_DIR_R DDRG
#define DIRECTION_R PG4
#define PORT_DIR_R PORTG

#define STEPPER_LEFT PH3
#define DDR_STEP_L  DDRH
#define PORT_STEP_L PORTH
#define DDR_DIR_L DDRH
#define DIRECTION_L PH4
#define PORT_DIR_L PORTH

void initPinsStepper (void);
void initTimer1Stepper(void);
void initTimer4Stepper(void);
void initStepper(void);

void speedStepperRight(int PWMRight);
void speedStepperLeft(int PWMLeft);

void toggleStepperDirectionRight(void);
void toggleStepperDirectionLeft(void);

extern volatile unsigned int stepCounterLeft;
extern volatile unsigned int stepCounterRight;
void clearStepCnt(void);


#endif // STEPPER_DRIVER_H_INCLUDED
