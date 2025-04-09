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
    int temp=tel;

    //pad 1
    while((distance_left<15)){
        rechtdoor();
    }
    //bocht 1
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
    //pad 2

    /*
    if(terminate==0){
        while((distance_left<15)){
            rechtdoor();
            telblokje();
            if(temp!=(tel+tel2)){
                stop();
                _delay_ms(1000);
                temp= tel+tel2;
            }
        }
    }
    //bocht 2
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
    //pad 3
    if(terminate==0){
        while((distance_left<15)){
            rechtdoor();
            telblokje();
            if(temp!=(tel+tel2)){
                stop();
                _delay_ms(1000);
                temp= tel+tel2;
            }
        }
    }
    */
}
