#ifndef IR_H_INCLUDED
#define IR_H_INCLUDED

#define pinnummer_ir PC7
#define pinnummer_ir2 PC6
#define ddr_irout DDRC
#define pin_ir PINC
#define ddr_led DDRC
#define led1 PC5
#define port_led PORTC

extern int tel;
void IR_init(void);
void IR_RUN(void);
void irRun2(void);
void IRSPAMMER(void);

#endif // IR_H_INCLUDED
