#include <msp430.h> 

#define LED_0 BIT0 //0x1
#define LED_OUT P1OUT
#define LED_DIR P1DIR
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	LED_DIR |= LED_0; //Set LED to output
	LED_OUT ^= LED_0;

	while (1){
	    __delay_cycles(100000);
	    P1OUT ^= LED_0;
	}
}
