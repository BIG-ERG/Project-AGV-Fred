#include "uitvoer.h"

#include <avr/io.h>
/*
extern int pakjes;// hoeveel pakjes er worden geteld
extern int letter;// hoeveel keer op plus is gedrukt
extern int lettertwee;// hoeveel keer op plus is gedrukt bij de tweede keer
*/

void uitvoer(void){

    init_ultrasoon();
    initStepper();
    IR_init();

    int terminate = 0;
    static int spaceAndTime = 0;        //om aan te geven waar binnen de uitvoer van het programma de agv zich bevindt in het geval van een noodstop actuatie

    //pad 1
    if(spaceAndTime==0){
        while((distance_left<15)){
            rechtdoor();
        }
        spaceAndTime++;
    }
    //bocht 1
    if(spaceAndTime==1){
        if(letter!=0){
            if(letter==1)
                linksom();
            else
                rechtsom();
        }
        else{
            stop();
            terminate ++;
        }
        spaceAndTime++;
    }
    //pad 2
    if(spaceAndTime==2){
        if(terminate==0){
            while((distance_left<15)){
                rechtdoor();
            }
        }
        spaceAndTime++;
    }
    //bocht 2
    if(spaceAndTime==3){
        if(letter!=0){
            if(letter==1)
                linksom();
            else
                rechtsom();
        }
        else{
            stop();
            terminate++;
        }
        spaceAndTime++;
    }
    //pad 3
    if(spaceAndTime==4){
        if(terminate==0){
            while((distance_left<15)){
                rechtdoor();
            }
        }
        spaceAndTime++;
    }
}

int terminator = 0;

void uitvoer2(void){

    init_ultrasoon();
    initStepper();
    IR_init();

    int terminate = 0;
    static int spaceAndTime = 0;        //om aan te geven waar binnen de uitvoer van het programma de agv zich bevindt in het geval van een noodstop actuatie

    //pad 1
    while(terminator == 0){
        if(spaceAndTime==0){
            rechtdoor2();
            spaceAndTime++;
        }
        //bocht 1
        if(spaceAndTime==1){
            if(letter!=0){
                if(letter==1)
                    linksom();
                else
                    rechtsom();
            }
            else{
                stop();
                terminate ++;
            }
            spaceAndTime++;
        }
        //pad 2
        if(spaceAndTime==2){
            rechtdoor2();
            spaceAndTime++;
        }
        //bocht 2
        if(spaceAndTime==3){
            if(letter!=0){
                if(letter==1)
                    linksom();
                else
                    rechtsom();
            }
            else{
                stop();
                terminate++;
            }
            spaceAndTime++;
        }
        //pad 3
        if(spaceAndTime==4){
            rechtdoor2();
            spaceAndTime++;
        }
    }
}
