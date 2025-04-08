/*
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"
#include "ultrasoon.h"
#include "interface.h"

int main(void)
{
    /*
    init_ultrasoon();
    initStepper();
    initNoodstop();
    */
    init_display();
    IR_init();

    while(1){
        IR_RUN();
        IR_RUN2();
        telblokje();
    }

    return 0;
}
