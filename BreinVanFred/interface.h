#ifndef interface_H_INCLUDED
#define interface_H_INCLUDED

// Aansluitingen:
// 29: SDI	-> PA7
// 25: SFTCLK	-> PA3
// 27: LCHCLK	-> PA5
#define SDI_BIT		PA7
#define DDR_SDI		DDRA
#define PORT_SDI	PORTA

#define SFTCLK_BIT	PA3
#define DDR_SFTCLK	DDRA
#define PORT_SFTCLK	PORTA

#define LCHCLK_BIT	PA5
#define DDR_LCHCLK	DDRA
#define PORT_LCHCLK	PORTA

#define back PA0 // pin 22
#define next PA4 // pin 26
#define plus PA2   // pin 24
#define start PA6 // pin 28
#define DDR_knop DDRA
#define PIN_knop PINA
#define PORT_knop PORTA

void init_display (void);
void send_data(char data);
void send_enable(int display_nummer);
void display(char data, int display_nummer);
void display_getal(unsigned int getal);
void aantal_pakje();
void telblokje(void);

extern int pakjes;// hoeveel pakjes er worden geteld
extern int letter;// hoeveel keer op plus is gedrukt
extern int lettertwee;// hoeveel keer op plus is gedrukt bij de tweede keer

#endif // interface_H_INCLUDED

