/*
 * main.c
 *
 *  Created on: Sept 26, 2017
 *  Last Edited: Sept 26, 2017
 *      Author: Lonnie Souder II
 */

#include <msp430.h> 

#define LED_OUT P1OUT
#define LED_DIR P1DIR


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer


    LED_DIR |= BIT0;            // Set LED to output
    LED_OUT &= ~BIT0;           // Initialize LED to OFF

    while (1){
        __delay_cycles(100000);
        LED_OUT ^= BIT0;        //Toggle LED
    }

}
