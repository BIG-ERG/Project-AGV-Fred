#include <avr/io.h>
#include <math.h>
#include <util/delay.h>

#include "navigatieLogica.h"

int padbreedte;

void metingPadbreedte(void){
    //neemt afmeting van de breedte van het pad in cm
    padbreedte = distance_left + distance_right + 13;
}

void vooruit(void){
    //agv rijdt ongecontroleerd vooruit
    speedStepperLeft(50);
    speedStepperRight(50);
}

void stop(void){
    //agv stopt met rijden
    speedStepperLeft(0);
    speedStepperRight(0);
}

void rechtdoor(void){
    int topspeed = 50;
    //while agv binnen het pad is
    while(distance_left<50){
            if (distance_right < distance_left){
                speedStepperLeft(60);
                speedStepperRight(topspeed);
            }
            if(distance_left < distance_right){
                speedStepperRight(60);
                speedStepperLeft(topspeed);
            }
        }
    //stop driving
    stop();
}

void rechtsom(void){
    clearStepCnt();
    while(stepCounterLeft<20){      //agv rijdt ietsjes verder buiten het pad
        vooruit();
    }
    clearStepCnt();
    toggleStepperDirectionRight();
    while(stepCounterLeft<(90/5.6)){   //agv draait 90 graden
        vooruit();
    }
    toggleStepperDirectionRight();
    clearStepCnt();
    while(stepCounterLeft<(padbreedte/5.6)){    //agv rijdt naar volgende pad
        vooruit();
    }
    toggleStepperDirectionRight();      //agv draati 90 graden
    clearStepCnt();
    while(stepCounterLeft<(90/5.6)){
        vooruit();
    }
    toggleStepperDirectionRight();
    clearStepCnt();
    vooruit();
    if(distance_left<25){           //agv is in het volgende pad
        stop();
    }
}
