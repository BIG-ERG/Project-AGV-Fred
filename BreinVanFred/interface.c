/*

*/

#ifndef F_CPU
#define F_CPU 16000000
#endif
#include <avr/io.h>
#include <util/delay.h>

#include "interface.h"
#include "IR.h"
#include "uitvoer.h"

int pakjes=0;
int letter=0;
int lettertwee=0;
static unsigned int segmentcodes[] = {
	0xFC, 0x60, 0xDA, 0xF2,
	0x66, 0xB6, 0xBE, 0xE0,
	0xFE, 0xF6, 0xEE, 0x3E,
	0x9C, 0x7A, 0x9E, 0x8E };

void init_display (void)
{
	// Initialiseer de pinnen voor datain, shiftclk en latchclk als output
	DDR_SDI    |= (1 << SDI_BIT);
	DDR_SFTCLK |= (1 << SFTCLK_BIT);
	DDR_LCHCLK |= (1 << LCHCLK_BIT);

	// Maak shiftclk en latchclk laag
	PORT_SFTCLK &= ~(1 << SFTCLK_BIT);
	PORT_LCHCLK &= ~(1 << LCHCLK_BIT);
}

void send_data(char data)
{
	for (unsigned i = 0; i < 8; i++)
	// Herhaal voor alle bits in een char
	{
		// Bepaal de waarde van de bit die je naar het schuifregister
		// wil sturen
		int bit = data & 1;
		data >>= 1;

		// Maak de juiste pin hoog of laag op basis van de bepaalde waarde
		// van het bit
		if (bit)
		{
			PORT_SDI |= (1 << SDI_BIT);
		}
		else
		{
			PORT_SDI &= ~(1 << SDI_BIT);
		}

		// Toggle shiftclk (hoeveel tijd moest het signaal minimaal hoog zijn?)
		// Puls moet minimaal 13 ns hoog zijn. Een clk cycle op de Arduino duurt
		// 62 ns, dus signaal kan hoog en de volgende cycle weer omlaag
		PORT_SFTCLK |= (1 << SFTCLK_BIT);
		PORT_SFTCLK &= ~(1 << SFTCLK_BIT);
	}
}

void send_enable(int display_nummer)
{
	send_data(~(0x10 << display_nummer));
}

void display(char data, int display_nummer)
{
	send_data(data);
	send_enable(display_nummer);

	// Toggle latchclk (hoeveel tijd moest het signaal minimaal hoog zijn?)
	// Puls moet minimaal 13 ns hoog zijn. Een clk cycle op de Arduino duurt
	// 62 ns, dus signaal kan hoog en de volgende cycle weer omlaag
	PORT_LCHCLK |= (1 << LCHCLK_BIT);
	PORT_LCHCLK &= ~(1 << LCHCLK_BIT);
}

void display_getal(unsigned int getal)
{
	for (int i = 0; i < 4; i++)
	{
		display(segmentcodes[getal%10], i);
		getal /= 10;
		_delay_ms(1);   // 1 kHz
	}
}

void aantal_pakje()
{

    static int plus_ingedrukt=0;
    static int next_ingedrukt=0;
    static int back_ingedrukt=0;
    static int next1_ingedrukt=0;
    static int back1_ingedrukt=0;
    static int plus1_ingedrukt=0;
    static int next2_ingedrukt=0;
    static int back2_ingedrukt=0;
    static int plus2_ingedrukt=0;
    static int start_ingedrukt=0;
    static int h=0;

    DDR_knop &=~((1<<back)|(1<<next)|(1<<plus)|(1<<start));
    PORT_knop |=((1<<back)|(1<<next)|(1<<plus)|(1<<start));



    switch(h)
    {

        case 0:
            {
                    display(segmentcodes[pakjes%10],0); // laat 4 nullen op display zien
                   _delay_ms(1);
                    display(segmentcodes[(pakjes/10)%10],1);
                    _delay_ms(1);
                    display(segmentcodes[(pakjes/100)%10],2);
                   _delay_ms(1);
                    display(segmentcodes[0],3);
                    _delay_ms(1);
                    display((char)~0b11111111,0123);
                    _delay_ms(1);

                 if (((PIN_knop&(1<<plus))==0)&&(plus_ingedrukt==0))
                 {
                  _delay_ms(10);
                        if (((PIN_knop&(1<<plus))==0)&&(plus_ingedrukt==0))
                        {
                            plus_ingedrukt=1;
                        }
                 }

                if (((PIN_knop&(1<<plus))!=0)&&(plus_ingedrukt==1))
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<plus))!=0&&(plus_ingedrukt==1)))
                    {
                    pakjes++;                                   // instellen hoeveel pakjes er geteld moeten worden als plus is ingedrukt
                    plus_ingedrukt=0;                           // en geef dat weer in oplopende getallen op display
                    }
                }
                if (((PIN_knop&(1<<next))==0)&&(next_ingedrukt==0)) // naar volgende stand
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<next))==0)&&(next_ingedrukt==0))
                    {
                        next_ingedrukt=1;
                    }
                }
                 if (((PIN_knop&(1<<next))!=0)&&(next_ingedrukt==1))
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<next))!=0)&&(next_ingedrukt==1))
                    {
                       next_ingedrukt=0;
                        h=1;
                    }
                }
                if (((PIN_knop&(1<<back))==0)&&(back_ingedrukt==0)) // aantal pakjes weer op 0 zetten en verwijderen hoeveel er is ingevoerd als back is ingedrukt
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<back))==0)&&(back_ingedrukt==0))
                    {
                        back_ingedrukt=1;
                        pakjes=0;
                    }
                }
                 if (((PIN_knop&(1<<back))!=0)&&(back_ingedrukt==1))
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<back))!=0)&&(back_ingedrukt==1))
                    {
                        display(segmentcodes[0],3);
                        _delay_ms(1);
                        display((char)~0b11111111,012);
                        _delay_ms(1);
                        back_ingedrukt=1;

                    }
                }
                break;
            }

        case 1:
        {

            switch(letter)
            {
                case 0:
                {
                    if(((PIN_knop&(1<<plus))==0)&&(plus1_ingedrukt==0)) // punt pisplay bij het streepje als plus is ingedrukt
                    {
                        _delay_ms(10);
                        if (((PIN_knop&(1<<plus))==0)&&(plus1_ingedrukt==0))
                        {
                            letter=1;
                            plus1_ingedrukt=1;
                        }
                    }
                    if(((PIN_knop&(1<<plus))!=0)&&(plus1_ingedrukt==1))
                    {
                    _delay_ms(10);
                        if (((PIN_knop&(1<<plus))!=0)&&(plus1_ingedrukt==1))
                        {

                            plus1_ingedrukt=0;
                        }
                    }
                            display(segmentcodes[1],3); // laat 1 - L r op display zien met punt bij -
                            _delay_ms(1);
                            display((char)~0b11111100,2);
                            _delay_ms(1);
                            display((char)~0b11100011,1);
                            _delay_ms(1);
                            display((char)~0b01110011,0);
                            _delay_ms(1);
                            display((char)~0b11111111,0123);
                            _delay_ms(1);
                    break;
                }
                case 1:
                {
                      if(((PIN_knop&(1<<plus))==0)&&(plus1_ingedrukt==0)) // punt display bij de letter L als plus is ingedrukt
                        {
                        _delay_ms(10);
                        if(((PIN_knop&(1<<plus))==0)&&(plus1_ingedrukt==0))
                            {
                            letter=2;
                            plus1_ingedrukt=1;
                            }
                        }
                    if((((PIN_knop&(1<<plus))!=0)&&(letter==1))&&(plus1_ingedrukt==1))
                    {
                    _delay_ms(10);
                        if ((((PIN_knop&(1<<plus))!=0)&&(letter==1))&&(plus1_ingedrukt==1))
                        {

                            plus1_ingedrukt=0;
                        }
                    }
                            display(segmentcodes[1],3); //laat 1 - L r op display zien met punt bij L
                            _delay_ms(1);
                            display((char)~0b11111101,2);
                            _delay_ms(1);
                            display((char)~0b11100010,1);
                            _delay_ms(1);
                            display((char)~0b01110011,0);
                            _delay_ms(1);
                            display((char)~0b11111111,0123);
                            _delay_ms(1);
                    break;
                }
                case 2:
                    {
                         if(((PIN_knop&(1<<plus))==0)&&(plus1_ingedrukt==0))// punt dispay bij de letter R als plus is ingedrukt
                        {
                        _delay_ms(10);
                        if(((PIN_knop&(1<<plus))==0)&&(plus1_ingedrukt==0))
                        {
                            letter=0;
                            plus1_ingedrukt=1;
                        }
                        }
                        if(((PIN_knop&(1<<plus))!=0)&&(plus1_ingedrukt==1))
                        {
                        _delay_ms(10);
                        if (((PIN_knop&(1<<plus))!=0)&&(plus1_ingedrukt==1))
                        {

                            plus1_ingedrukt=0;
                        }
                        }
                            display(segmentcodes[1],3);         //laat 1 - L r op display zien met punt bij r
                            _delay_ms(1);
                            display((char)~0b11111101,2);
                            _delay_ms(1);
                            display((char)~0b11100011,1);
                            _delay_ms(1);
                            display((char)~0b01110010,0);
                            _delay_ms(1);
                            display((char)~0b11111111,0123);
                            _delay_ms(1);
                        break;
                    }

            }

             if (((PIN_knop&(1<<next))==0)&&(next1_ingedrukt==0)) // naar volgede stand als next is ingedrukt
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<next))==0)&&(next1_ingedrukt==0))
                    {
                        next1_ingedrukt=1;
                    }
                }
                 if (((PIN_knop&(1<<next))!=0)&&(next1_ingedrukt==1))
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<next))!=0)&&(next1_ingedrukt==1))
                    {
                        next1_ingedrukt=0;
                        h=2;
                    }
                }
                if (((PIN_knop&(1<<back))==0)&&(back1_ingedrukt==0)) // naar vorige stand als back is ingedrukt
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<back))==0)&&(back1_ingedrukt==0))
                    {
                        letter=0;
                        back1_ingedrukt=1;
                    }
                }
                 if (((PIN_knop&(1<<back))!=0)&&(back1_ingedrukt==1))
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<back))!=0)&&(back1_ingedrukt==1))
                    {
                        h=0;
                        back1_ingedrukt=0;
                    }
                }
             break;
        }
        case 2:
            {

            switch(lettertwee)
            {
                case 0:
                {
                    if(((PIN_knop&(1<<plus))==0)&&(plus2_ingedrukt==0)) // punt pisplay bij het streepje als plus is ingedrukt
                    {
                        _delay_ms(10);
                        if (((PIN_knop&(1<<plus))==0)&&(plus2_ingedrukt==0))
                        {
                            lettertwee=1;
                            plus2_ingedrukt=1;
                        }
                    }
                    if(((PIN_knop&(1<<plus))!=0)&&(plus2_ingedrukt==1))
                    {
                    _delay_ms(10);
                        if (((PIN_knop&(1<<plus))!=0)&&(plus2_ingedrukt==1))
                        {

                            plus2_ingedrukt=0;
                        }
                    }
                            display(segmentcodes[2],3);      // laat 1 - L r op display zien met punt bij -
                            _delay_ms(1);
                            display((char)~0b11111100,2);
                            _delay_ms(1);
                            display((char)~0b11100011,1);
                            _delay_ms(1);
                            display((char)~0b01110011,0);
                            _delay_ms(1);
                            display((char)~0b11111111,0123);
                            _delay_ms(1);
                    break;
                }
                case 1:
                {
                      if(((PIN_knop&(1<<plus))==0)&&(plus2_ingedrukt==0)) // punt display bij de letter L als plus is ingedrukt
                        {
                        _delay_ms(10);
                        if(((PIN_knop&(1<<plus))==0)&&(plus2_ingedrukt==0))
                            {
                            lettertwee=2;
                            plus2_ingedrukt=1;
                            }
                        }
                    if((((PIN_knop&(1<<plus))!=0)&&(letter==1))&&(plus2_ingedrukt==1))
                    {
                    _delay_ms(10);
                        if ((((PIN_knop&(1<<plus))!=0)&&(letter==1))&&(plus2_ingedrukt==1))
                        {

                            plus2_ingedrukt=0;
                        }
                    }
                            display(segmentcodes[2],3);         //laat 1 - L r op display zien met punt bij L
                            _delay_ms(1);
                            display((char)~0b11111101,2);
                            _delay_ms(1);
                            display((char)~0b11100010,1);
                            _delay_ms(1);
                            display((char)~0b01110011,0);
                            _delay_ms(1);
                            display((char)~0b11111111,0123);
                            _delay_ms(1);
                    break;
                }
                case 2:
                    {
                         if(((PIN_knop&(1<<plus))==0)&&(plus2_ingedrukt==0))        // punt dispay bij de letter R als plus is ingedrukt
                        {
                        _delay_ms(10);
                        if(((PIN_knop&(1<<plus))==0)&&(plus2_ingedrukt==0))
                        {
                            lettertwee=0;
                            plus2_ingedrukt=1;
                        }
                        }
                        if(((PIN_knop&(1<<plus))!=0)&&(plus2_ingedrukt==1))
                        {
                        _delay_ms(10);
                        if (((PIN_knop&(1<<plus))!=0)&&(plus2_ingedrukt==1))
                        {

                            plus2_ingedrukt=0;
                        }
                        }
                            display(segmentcodes[2],3);          //laat 1 - L r op display zien met punt bij r
                            _delay_ms(1);
                            display((char)~0b11111101,2);
                            _delay_ms(1);
                            display((char)~0b11100011,1);
                            _delay_ms(1);
                            display((char)~0b01110010,0);
                            _delay_ms(1);
                            display((char)~0b11111111,0123);
                            _delay_ms(1);
                        break;
                    }

            }

             if (((PIN_knop&(1<<next))==0)&&(next2_ingedrukt==0)) // ga naar volgende stand als next is ingedrukt
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<next))==0)&&(next2_ingedrukt==0))
                    {
                        next2_ingedrukt=1;
                    }
                }
                 if (((PIN_knop&(1<<next))!=0)&&(next2_ingedrukt==1))
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<next))!=0)&&(next2_ingedrukt==1))
                    {
                        next2_ingedrukt=0;
                        h=3;
                    }
                }
                if (((PIN_knop&(1<<back))==0)&&(back2_ingedrukt==0))// ga naar vorige stand als back is ingedrukt
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<back))==0)&&(back2_ingedrukt==0))
                    {
                        lettertwee=0;
                        back2_ingedrukt=1;
                    }
                }
                 if (((PIN_knop&(1<<back))!=0)&&(back2_ingedrukt==1))
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<back))!=0)&&(back2_ingedrukt==1))
                    {
                        h=1;
                        back2_ingedrukt=0;
                    }
                }
             break;
            }
        case 3:     //transfer naar rest van de code
            {
                if (((PIN_knop&(1<<start))==0)&&(start_ingedrukt==0))
                {
                    _delay_ms(10);
                    if (((PIN_knop&(1<<start))==0)&&(start_ingedrukt==0))
                    {
                        start_ingedrukt=1;
                    }
                }
                 if (((PIN_knop&(1<<start))!=0)&&(start_ingedrukt==1))
                {
                _delay_ms(10);
                    if (((PIN_knop&(1<<start))!=0)&&(start_ingedrukt==1)) // start met rijden als start is indgedukt
                    {
                        // start met rijden
                        start_ingedrukt=0;
                        uitvoer();
                    }
                }
                            //display "fred" totdat gebruiker op start drukt
                            display((char)~0b01110001,3); // geef fred op display weer
                            _delay_ms(1);
                            display((char)~0b01110011,2);
                            _delay_ms(1);
                            display((char)~0b01100001,1);
                            _delay_ms(1);
                            display((char)~0b10000101,0);
                            _delay_ms(1);
                            display((char)~0b11111111,0123);
                            _delay_ms(1);

                            //start programma
                }
                break;


        }

}

void telblokje()
{

                    display(segmentcodes[(tel+tel2)%10],0);
                   _delay_ms(1);
                    display(segmentcodes[((tel+tel2)/10)%10],1);
                    _delay_ms(1);
                    display(segmentcodes[((tel+tel2)/100)%10],2);
                   _delay_ms(1);
                    display(segmentcodes[((tel+tel2)/1000)%10],3);
                    _delay_ms(1);
                    display((char)~0b11111111,0123);
                    _delay_ms(1);
}

