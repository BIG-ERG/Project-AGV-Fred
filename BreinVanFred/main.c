/*
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"



int main(void)
{
    init_display();
    initNoodstop();

    while(1){
        aantal_pakje();
        //rechtdoor();
        //telblokje();
    }

    return 0;
}
