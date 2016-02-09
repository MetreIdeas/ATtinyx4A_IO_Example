/*
 * ATtinyx4A_IO_Example.c
 *
 * Created: 02/09/2016
 * Author: Will Sakran
 * Metre Ideas and Design
 *
 * This program uses an external interrupt (INT0 on pin PB2) to step through turning various
 * output pins on and off. Triggering the interrupt will turn on the next output in sequence
 * from PA0 through PA7. Outputs are configured as active high.
 *
 * This example also includes code for putting the chip into a low power idle state. When
 * sleeping, the chip is woken up by the external interrupt.
 *
 * Developed for use with Atmel ATtiny24A / ATtiny44A / ATtiny84A
 * For ATtiny24A/44A/84A Prototyping boards go to
 * www.metreideas.com
 *
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

/* Set the correct clock frequency based on fuse settings or external clock/crystal
 * has to be done before including delay.h */
#define F_CPU	1000000UL
#include <util/delay.h>

volatile uint8_t	port_pin=0x01;

void board_init(void);

/**
 * \brief Main routine
 */
int main(void)
{
	board_init();
		
	sei();									// Enable interrupts
	
	// Set up the external interrupt	
	MCUCR |= (1 << ISC01);					// set INT0 to trigger on a falling edge
	GIMSK |= (1 << INT0);					// enable the external interrupt
	GIFR |= (1 << INTF0);					// clear the external interrupt flag
	
	while (1) {
		PORTA = 0x00;						// turn off all port A pins
		PORTA |= port_pin;					// turn on the active output pin
		
		// No sense is staying awake, so go to sleep and wait for interrupt
		set_sleep_mode(SLEEP_MODE_IDLE);	// set the sleep mode
		sleep_enable();						// set the sleep enable bit
		sleep_mode();						// Zzzzzz
		
		// external interrupt will cause code to resume here after ISR
		sleep_disable();					// clear the sleep enable bit
		  
	} // end while
} // end main


/* External interrupt vector */
ISR(EXT_INT0_vect)
{
	if(port_pin == 0x80)
	{
		port_pin = 0x01;		// reset to the beginning of the sequence (pin PA0)
		return;
	}
	
	port_pin = port_pin << 1;	// shift the port pin by one bit
}


void board_init(void)
{
	DDRA = 0xFF;	// Configure Port A as all outputs
	PORTA = 0x00;	// Set all port A outputs to 0

	PORTB = 0x04;	// enable pull-up on PB2 (INT0)
}