#include "noodstop.h"
#include "navigatieLogica.h"

#include <avr/interrupt.h>
#include <avr/io.h>

void initNoodstop(void){
    DDR_NOOD &= ~ (1<<NOODKNOP);

    EIMSK |= (1<<NOODKNOP);       //ENABLE HARDWARE INTERRUPT ON PD0
    EICRA |= (0<<ISC01) | (1<<ISC00);   //Any edge of INTn generates asynchronously an interrupt request
    sei();
}

void SAFETYFIRST(void){
    static int safety = 0;
    if(safety==0)
        safety = 1;
    else
        safety = 0;
    while(safety==1){
        stop();
    }
}

ISR(INT0_vect){
    SAFETYFIRST();
}
