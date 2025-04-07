/*
deze code is bedoeld om met behulp van een or gate twee ultrasoon sensoren uit te lezen met alleen 1 timer!!
zie elektrisch schema voor verdere uitleg
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ultrasoon.h"

void init_timer5(void){
    //set timer mode 15
    TCCR5A = (1<<COM5B1) | (1<<COM5C1) | (1<<WGM51) | (1<<WGM50); //set output compare on B and C
    TCCR5B = (1<<ICES5) | (1<<WGM53) | (1<<WGM52) | (1<<CS51);  //set input capture to rising edge and prescaler 8
    //set interrupt register for input capture and overflow
    TIMSK5 = (1<<ICIE5) | (1<<TOIE5);
    //define top value
    OCR5A = 0XFFFF;
    //set trigger start signal
    OCR5B = 20;
    OCR5C = 20;
    //set enable interrupt
    sei();
}

void init_pins_ultrasoon(void){
    //set trigger pins to output
    DDRL |= (1<<Pin_Trig_Left);
    DDRL |= (1<<Pin_Trig_Right);
    //set trigger pins to low
    PORTL &= ~(1<<Pin_Trig_Left);
    PORTL &= ~(1<<Pin_Trig_Right);
    //set echo pin to input
    DDRL &= ~(1<<Pin_echo);
}

void init_ultrasoon(void){
    init_pins_ultrasoon();
    init_timer5();
}

volatile int distance_right;
volatile int distance_left;
volatile int current_sensor=0;

ISR(TIMER5_OVF_vect){
    //set input capture to rising edge
    TCCR5B |= (1<<ICES5);
}

ISR(TIMER5_CAPT_vect){
    static volatile int start_time;
    // If interrupt is set to rising edge
    if (TCCR5B & (1 << ICES5)) {
        start_time = ICR5;
        TCCR5B &= ~(1 << ICES5);  // Switch to falling edge
    }
    else {
        int distance = (ICR5 - start_time) / 117;  // Calculate distance in cm

        if (current_sensor == 0) {
            distance_left = distance;  // Store distance for Sensor A
        } else {
            distance_right = distance;  // Store distance for Sensor B
        }

        //switch between sensors
        if (current_sensor == 0) {
            current_sensor = 1;  // Switch to Sensor B
            TCCR5A &= ~(1 << COM5C1);  // Turn off Sensor Left
            TCCR5A |= (1 << COM5B1);   // Turn on Sensor Right
        }
        else {
            current_sensor = 0;  // Switch to Sensor A
            TCCR5A &= ~(1 << COM5B1);  // Turn off Sensor Right
            TCCR5A |= (1 << COM5C1);   // Turn on Sensor Left
        }
    }
}
