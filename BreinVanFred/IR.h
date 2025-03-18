#ifndef IR_H_INCLUDED
#define IR_H_INCLUDED

#define pinnummer_ir PC7
#define ddr_irout DDRC
#define pin_ir PINC
#define ddr_led DDRB
#define led1 PB7
#define port_led PORTB

extern int tel;
void IR_init();
void IR_RUN();

#endif // IR_H_INCLUDED
