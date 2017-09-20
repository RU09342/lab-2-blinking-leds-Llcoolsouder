/*
 * main.c
 *
 *  Created on: Sept 13, 2017
 *  Last Edited: Sept 13, 2017
 *      Author: Lonnie Souder II
 */

#include <msp430.h> 

#define LED_OUT P2OUT
#define LED_DIR P2DIR

#define BTN_RES P1REN
#define BTN_DIR P1DIR
#define BTN_IN  P1IN



int main(void)

{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
                                // to activate previously configured port settings

    P1SEL0 &= ~BIT1;            // Set P1.1 (Button) to GPIO
    P1SEL1 &= ~BIT1;
    P2SEL0 &= ~BIT0;            // Set P2.0 (LED) to GPIO
    P2SEL1 &= ~BIT0;

    LED_DIR |= 0x0001;          // Set LED to output
    LED_OUT &= 0x0000;          // Initialize LED to OFF

    BTN_DIR &= ~0x0002;         // Set Button as input
    BTN_RES |= 0x0002;          // Turn on pullup resistor

    unsigned x = 0;
    unsigned y = 0;
    unsigned count = 0;
    unsigned sample = 0;
    unsigned i = 0;
    while (1) {
        for (i = 500; i>0; i--) {
            if (!(BTN_IN & BIT1))
                    sample++;
        }
        if (sample/500 > 0.5) {
            count++;
            switch (count % 3) {
            case (0) : x = 5000; break;
            case (1) : x = 10000; break;
            case (2) : x = 50000; break;
            }
        }
            LED_OUT ^= BIT0;
            while (y < x) {
                if (!(BTN_IN & BIT1))
                    break;
                y++;
            }
            y = 0;
            sample = 0;
    }
    /*
    int delay;
    while (1){
        while (!(BTN_IN & BIT1)){   // if button is pushed
            delay = 0;
            LED_OUT ^= BIT0;        // Toggle LED
            while (delay<10000){    // if button is released
                 if (BTN_IN & BIT1)
                     break;         // Break out of
                 else
                     delay++;
            }
        }
        LED_OUT &= ~BIT0;
    }
*/
}
