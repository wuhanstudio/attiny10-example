/*
 * attiny10.c
 *
 * Created: 2019/1/3 12:42:24
 * Author : WuHan
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

// Check ISR here
// #include <avr/iotn10.h>

char name[] = "wuhanstudio";
int state;
int main(void)
{
	CLKMSR = 0x00;
	
	// PB0-2 OUTPUT
	DDRB = (1<<DDB0) | (1<<DDB1) | (1<<DDB2);
	PUEB = ~(1<<PUEB0) & ~(1<<PUEB1) & ~(1<<PUEB2);
	PORTB |= 1<<PORTB2;

	// Initialize PWM
	TCCR0A =  (1 << COM0A1) | (1 << COM0B1) | (1 << COM0B0) | (1 << WGM00);
	TCCR0B =  (1 << WGM02)  | (1 << CS00);
	OCR0A  =  205;  // Duty 80 
	OCR0B  =  205;  // Duty 20
	
    /* Replace with your application code */
    while (1) 
    {
		_delay_ms(20);
		PORTB &= ~(1 << PORTB2);
		_delay_ms(20);
		PORTB |= 1 << PORTB2;
	}
}

// ISR(TIM0_OVF_vect){
	
// }
