#ifndef NAVIGATIELOGICA_H_INCLUDED
#define NAVIGATIELOGICA_H_INCLUDED

#include "navigatieLogica.h"
#include "ultrasoon.h"
#include "stepperDriver.h"
#include "IR.h"
#include "uitvoer.h"

void vooruit(void);
void stop(void);
void rechtdoor(void);
void rechtdoor2(void);
void rechtsom(void);
void linksom(void);
void metingPadbreedte(void);
int ramping(int originalValue , int value);

#endif // NAVIGATIELOGICA_H_INCLUDED
