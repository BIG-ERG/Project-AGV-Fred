/*
 */
#include "IR.h"
#include "interface.h"
#include <avr/io.h>
#include<util/delay.h>

int tel=-1;
int tel2=-1;

void IR_init()
{
    ddr_irout&=~(1<<pinnummer_ir);
    ddr_led|=(1<<led1);
    port_led|=(1<<led1);

    ddr_irout&=~(1<<pinnummer_ir2);
}

void IR_RUN()// check of pin hoog of laag is
{
    static int gedetecteerd = 0;
    if ((pin_ir&(1<<pinnummer_ir))==0)
    {
        _delay_ms(20); // debounce
        if ((pin_ir&(1<<pinnummer_ir))==0)
        {
            gedetecteerd=0;
            port_led&=~(1<<led1);//led aan
        }
    }
    else
    {
        _delay_ms(20); // debounce
        if ((pin_ir&(1<<pinnummer_ir))!=0)
        {
            if(!gedetecteerd)
            {
                tel++;
            }
            gedetecteerd=1;
            port_led|=(1<<led1);//led uit
        }
    }
}

void IR_RUN2()// check of pin hoog of laag is
{
    static int gedetecteerd = 0;
    if ((pin_ir&(1<<pinnummer_ir2))==0)
    {
        _delay_ms(20); // debounce
        if ((pin_ir&(1<<pinnummer_ir2))==0)
        {
            gedetecteerd=0;
            port_led&=~(1<<led1);//led aan
        }
    }
    else
    {
        _delay_ms(20); // debounce
        if ((pin_ir&(1<<pinnummer_ir2))!=0)
        {
            if(!gedetecteerd)
            {
                tel2++;
            }
            gedetecteerd=1;
            port_led|=(1<<led1);//led uit
        }
    }
}

void IRSPAMMER(void){
    IR_RUN();
    IR_RUN2();
}
