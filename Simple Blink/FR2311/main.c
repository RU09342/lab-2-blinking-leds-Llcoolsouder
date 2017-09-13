/*
 * main.c
 *
 *  Created on: Sept 13, 2017
 *  Last Edited: Sept 13, 2017
 *      Author: Lonnie Souder II
 */

#include <msp430.h> 

#define LED_OUT P1OUT
#define LED_DIR P1DIR


int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
                                // to activate previously configured port settings

	LED_DIR |= 0x0001;          // Set LED to output
	LED_OUT &= 0x0000;          // Initialize LED to OFF

	while (1){
	    __delay_cycles(100000);
	    LED_OUT ^= BIT0;        //Toggle LED
	}

}
