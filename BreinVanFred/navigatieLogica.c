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
    int directionState=0;
    //while agv binnen het pad is
    while(distance_left<50){
        if (distance_right==distance_left) {
            if(directionState!=1){
                speedStepperLeft(topspeed);
                speedStepperRight(topspeed);
                directionState = 1;
            }
        }
        else{
            if (distance_right < distance_left){
                if(directionState!=2){
                speedStepperLeft(60);
                speedStepperRight(topspeed);
                directionState = 2;
                }
            }
            if(distance_left < distance_right){
                if(directionState!=3){
                speedStepperRight(60);
                speedStepperLeft(topspeed);
                directionState = 3;
                }
            }
        }
    }
    //stop driving
    stop();
}

void rechtsom(void){
    clearStepCnt();
    while(stepCounterLeft<2100){      //agv rijdt ietsjes verder buiten het pad
        vooruit();
    }
    clearStepCnt();
    toggleStepperDirectionRight();
    while(stepCounterLeft<2150){   //agv draait 90 graden
        vooruit();
    }
    toggleStepperDirectionRight();
    clearStepCnt();
    while(stepCounterLeft<(7100)){    //agv rijdt naar volgende pad
        vooruit();
    }
    toggleStepperDirectionRight();      //agv draati 90 graden
    clearStepCnt();
    while(stepCounterLeft<(2150)){
        vooruit();
    }
    toggleStepperDirectionRight();
    clearStepCnt();
    vooruit();
    while(distance_left>25){           //agv is in het volgende pad
        vooruit();
    }
    stop();
}

void linksom(void){
    clearStepCnt();
    while(stepCounterLeft<2100){      //agv rijdt ietsjes verder buiten het pad
        vooruit();
    }
    clearStepCnt();
    toggleStepperDirectionLeft();
    while(stepCounterLeft<2150){   //agv draait 90 graden
        vooruit();
    }
    toggleStepperDirectionLeft();
    clearStepCnt();
    while(stepCounterLeft<(7100)){    //agv rijdt naar volgende pad
        vooruit();
    }
    toggleStepperDirectionLeft();      //agv draati 90 graden
    clearStepCnt();
    while(stepCounterLeft<(2150)){
        vooruit();
    }
    toggleStepperDirectionLeft();
    clearStepCnt();
    vooruit();
    while(distance_left>25){           //agv is in het volgende pad
        vooruit();
    }
    stop();
}
