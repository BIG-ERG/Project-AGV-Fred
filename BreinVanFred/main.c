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

    vooruit();
    rechtsom();
    vooruit();
    return 0;
}
