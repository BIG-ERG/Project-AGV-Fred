/*
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"
#include "ultrasoon.h"

int main(void)
{
    init_ultrasoon();
    initStepper();
    initNoodstop();

    while(1){
    rechtdoor();
    rechtsom();
    }

    return 0;
}
