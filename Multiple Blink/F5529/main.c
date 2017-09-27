/*
 * main.c
 *
 *  Created on: Sept 26, 2017
 *  Last Edited: Sept 26, 2017
 *      Author: Lonnie Souder II
 */

#include <msp430.h> 

#define LED1_OUT P1OUT
#define LED1_DIR P1DIR
#define LED2_OUT P4OUT
#define LED2_DIR P4DIR


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    LED1_DIR |= BIT0;           // Set LED to output
    LED1_OUT &= ~BIT0;          // Initialize LED to OFF
    LED2_DIR |= BIT7;           // Set LED to output
    LED2_OUT |= BIT7;           // Initialize LED to ON

    while (1){
        LED1_OUT ^= BIT0;       //Toggle LED
        LED2_OUT ^= BIT7;       //Toggle LED
        __delay_cycles(200000);
        LED1_OUT ^= BIT0;       //Toggle LED
        __delay_cycles(100000);
        LED2_OUT ^= BIT7;       //Toggle LED
        __delay_cycles(100000);
        LED1_OUT ^= BIT0;       //Toggle LED
        __delay_cycles(200000);

    }

}