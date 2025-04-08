/*
 */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "main.h"



int main(void)
{
    init_display();

    while(1){
        aantal_pakje();
    }

    return 0;
}
