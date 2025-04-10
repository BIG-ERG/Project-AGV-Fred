#ifndef NOODSTOP_H_INCLUDED
#define NOODSTOP_H_INCLUDED

#include "interface.h"

#define NOODKNOP PD0
#define DDR_NOOD DDRD
#define PORT_NOOD PORTD
#define PIN_NOOD PIND

void initNoodstop(void);
void SAFETYFIRST(void);

#endif // NOODSTOP_H_INCLUDED
