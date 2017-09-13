/*
 * main.c
 *
 *  Created on: Sept 13, 2017
 *  Last Edited: Sept 13, 2017
 *      Author: Lonnie Souder II
 */

#include <msp430.h> 

#define LED1_OUT P1OUT
#define LED1_DIR P1DIR
#define LED2_OUT P2OUT
#define LED2_DIR P2DIR


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
                                // to activate previously configured port settings

    LED1_DIR |= 0x0001;         // Set LED to output
    LED1_OUT &= 0x0000;         // Initialize LED to OFF
    LED2_DIR |= 0x0001;         // Set LED to output
    LED2_OUT |= 0x0001;         // Initialize LED to ON

    while (1){
        LED1_OUT ^= BIT0;       //Toggle LED
        LED2_OUT ^= BIT0;       //Toggle LED
        __delay_cycles(200000);
        LED1_OUT ^= BIT0;       //Toggle LED
        __delay_cycles(100000);
        LED2_OUT ^= BIT0;       //Toggle LED
        __delay_cycles(100000);
        LED1_OUT ^= BIT0;       //Toggle LED
        __delay_cycles(200000);

    }

}
