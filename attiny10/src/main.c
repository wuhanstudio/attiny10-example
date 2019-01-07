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

/* -Choose Examples Here- */
// #define LED_EXAMPLE
#define PWM_EXAMPLE
// #define ADC_EXAMPLE
/* --------------------- */

// Examples
void adc_led();
void blink_led();
void pwm_led();

/* ---------------- */
#ifdef LED_EXAMPLE
	#define USE_LED
#endif

#ifdef PWM_EXAMPLE
	#define USE_LED
	#define USE_PWM
#endif

#ifdef ADC_EXAMPLE
	#define USE_LED
	#define USE_PWM
	#define USE_ADC
#endif
/* ---------------- */

void setup() {
	// Internal 8MHz, prescaler 1
	CCP    = 0xD8;
	CLKMSR = 0x00;
	CCP    = 0xD8;
	CLKPSR = 0X00;

#ifdef USE_LED
	// Initialize PB0-2 OUTPUT
	DDRB  = (1<<DDB0) | (1<<DDB1) | (1<<DDB2);
	PUEB  = ~(1<<PUEB0) & ~(1<<PUEB1) & ~(1<<PUEB2);
	PORTB = (1<<PORTB0) | (1<<PORTB1) | (1<<PORTB2);
#endif

#ifdef USE_PWM
	// Initialize PWM
	TCCR0A =  (1 << COM0A1) | (1 << COM0B1) | (1 << COM0B0) | (1 << WGM00);
	TCCR0B =  (1 << WGM02)  | (1 << CS00);
#endif

#ifdef USE_ADC
	// Initialize ADC
	ADMUX = (1 << MUX1);
	ADCSRA = (1<<ADEN)|(1<<ADPS1)|(1<<ADPS1)|(1<<ADPS0);
#endif

}

int main(void) {
	setup();

	/* Replace with your application code */
	while(1)
	{
	#ifdef LED_EXAMPLE
		blink_led();
	#endif

	#ifdef PWM_EXAMPLE
		pwm_led();
	#endif

	#ifdef ADC_EXAMPLE
		adc_led();
	#endif
	}
}

void blink_led() {
	_delay_ms(1000);
	PORTB = ~(1 << PORTB0) & ~(1 << PORTB1);
	_delay_ms(1000);
	PORTB = (1 << PORTB0) | (1 << PORTB1);
}

void pwm_led() {
	int i;
	for (i = 0; i< 256; i ++) 
	{
		OCR0A  =  i;  // Duty 
		OCR0B  =  i;  // Duty 
		_delay_ms(10);
	}
	_delay_ms(200);
	for (i = 255; i> 0; i --) 
	{
		OCR0A  =  i;  // Duty 
		OCR0B  =  i;  // Duty 
		_delay_ms(10);
	}
}

void adc_led() {
	unsigned char val;
	ADCSRA |= (1<<ADSC);
	while(ADCSRA & (1<<ADSC));
	val = (unsigned char)ADCL;
	OCR0A = val;
	OCR0B = val;
}

// ISR(TIM0_OVF_vect){
	
// }
