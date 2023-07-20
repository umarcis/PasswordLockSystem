/*
 * passwordlockRECEIVER.c
 *
 * Created: 7/28/2022 9:14:02 PM
 * Author : Muhammad Umar
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>
int main(void)
{
	DDRD&=~(1<<PD0);
	DDRA=0x00;
	DDRB = 0xFF;
	DDRE = 0b111;
	UBRR0H=0x00;
	UBRR0L=0x05;
	UCSR0B|=(1<<RXEN0);
	UCSR0C=(1<<USBS0)|(3<<UCSZ00);
	char og_pass[4]={3,3,6,6};
	int index =0;
	unsigned char receiveData;
	while (1)
	{
		receiveData=0;
		while(!(UCSR0A&(1<<RXC0)))
		{
			if ((PINA&1)==1)
			{
				PORTB=0;
				PORTE = 0b000;
				_delay_ms(100);
				PORTE = 0b001;
				PORTE = 0b000;
				index=0;
			}
		}
		receiveData=UDR0;
		if (receiveData==og_pass[index])
		{
			index++;
		}
		if (index==4)
		{
			PORTB = 1;
			PORTE = 0b001;
			_delay_ms(100);
			PORTE = 0b000;
		}
	}
}

