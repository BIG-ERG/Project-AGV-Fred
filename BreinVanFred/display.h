#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

// Aansluitingen:
// 8: SDI	-> PH5
// 7: SFTCLK	-> PH4
// 4: LCHCLK	-> PG5
#define SDI_BIT		PH5
#define DDR_SDI		DDRH
#define PORT_SDI	PORTH

#define SFTCLK_BIT	PH4
#define DDR_SFTCLK	DDRH
#define PORT_SFTCLK	PORTH

#define LCHCLK_BIT	PG5
#define DDR_LCHCLK	DDRG
#define PORT_LCHCLK	PORTG

void init_display (void);
void send_data(char data);
void send_enable(int display_nummer);
void display(char data, int display_nummer);
void display_getal(unsigned int getal);


#endif // DISPLAY_H_INCLUDED


