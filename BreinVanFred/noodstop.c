#include "noodstop.h"
#include "navigatieLogica.h"
#include "uitvoer.h"

#include <avr/interrupt.h>
#include <avr/io.h>

void initNoodstop(void){
    DDR_NOOD &= ~(1<<NOODKNOP);
    PORT_NOOD |= (1<<NOODKNOP);

    EIMSK |= (1<<INT0);       //ENABLE HARDWARE INTERRUPT ON PD0
    EICRA |= (0<<ISC01) | (1<<ISC00);   //Any edge of INTn generates asynchronously an interrupt request
    sei();
}

ISR(INT0_vect){
    while((PIN_NOOD & (1<<NOODKNOP))&&(!(PIN_knop&(1<<start))))     //while noodknop ingedrukt en start niet ingedrukt is (twee handeling voor noodstop)
        stop();

    uitvoer();
}
