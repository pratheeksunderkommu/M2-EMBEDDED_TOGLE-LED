_CPPUNWIND#ifndef F_CPU
#define F_CPU 16000000UL // telling controller crystal frequency (16 MHz AVR ATMega328P)
#endif

#include <avr/io.h> //header to enable data flow control over pins. Defines pins, ports, etc.
#include <util/delay.h> //header to enable delay function in program

#define BUTTON1 1 // button switch connected to port B pin 1

#define LED1 0 // Led1 connected to port B pin 0
#define LED2 1 // Led2 connected to port C pin 1
#define LED3 2 // Led3 connected to port D pin 2

#define DEBOUNCE_TIME 25 // time to wait while "de-bouncing" button 
#define LOCK_INPUT_TIME 300 // time to wait after a button press

void init_ports_mcu()
{
	DDRB=0xFFu; //	Set all pins of the PORTB as output.
	DDRB &= ~(1<<BUTTON1);//Makes first pin of PORTB as Input
	PORTB = 0xFF;  // Set all pins of the PORTB as HIGH. Led is turn on, also the internal Pull Up resistor of first pin PORTB is enable. 

	
	DDRC=0xFFu; //	Set all pins of the PORTC as output.
	PORTC=0x00u; // Set all pins of PORTC low which turns it off.

	DDRD=0xFFu; //	Set all pins of the PORTD as output.
	PORTD=0x00u; // Set all pins of PORTD low which turns it off.
}

unsigned char button_state()
{
	/* the button is pressed when BUTTON1 bit is clear */
	if (!(PINB & (1<<BUTTON1)))
	{
		_delay_ms(DEBOUNCE_TIME);
		if (!(PINB & (1<<BUTTON1))) return 1;
	}
	return 0;
}

int main (void)
{
	unsigned char n_led = 1; // LED number is on now
	init_ports_mcu();
	while (1)
	{
		if (button_state()) // If the button is pressed, toggle the LED's state and delay for 300ms (#define LOCK_INPUT_TIME)
		{

			switch(n_led){
			    case 1:
				  PORTB ^= (1<<LED1); // toggling the current state of the pin LED1. LED1 is turn off.
				  PORTC ^= (1<<LED2); // toggling the current state of the pin LED2. LED2 is turn on.
				break;
				case 2:
				  PORTC ^= (1<<LED2); // toggling the current state of the pin LED2. LED2 is turn off.
				  PORTD ^= (1<<LED3); // toggling the current state of the pin LED3. LED3 is turn on.
				break;
				case 3:
				   PORTD ^= (1<<LED3); // toggling the current state of the pin LED3. LED3 is turn off.
				   PORTB ^= (1<<LED1); // toggling the current state of the pin LED1. LED1 is turn on.
				 n_led=0; // reset LED number
				break;
			}
			n_led++; // next LED is turn on 
			_delay_ms(LOCK_INPUT_TIME); 
		}
	}
	return (0); 
}