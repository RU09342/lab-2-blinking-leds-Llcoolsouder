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

#define BTN_RES P1REN
#define BTN_DIR P1DIR
#define BTN_IN  P1IN



int main(void)

{
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer

    P1SEL &= ~(BIT0 | BIT3);            // Set P1.0 (LED) and P1.3 (Button) to GPIO
    P1SEL2 &= ~(BIT0 | BIT3);

    LED_DIR |= BIT0;                    // Set LED to output
    LED_OUT |= BIT0;                    // Initialize LED to ON

    BTN_DIR &= ~BIT3;                   // Set Button as input

    BTN_RES |= BIT3;                    // Turn on pullup resistor
    P1OUT |= BIT3;

    unsigned x = 0;
    unsigned y = 0;
    unsigned count = 0;
    float sample = 0;
    unsigned i = 0;
    while (1) {
        for (i = 1000; i>0; i--) {
            if (!(BTN_IN & BIT3))
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
                if (!(BTN_IN & BIT3))
                    break;
                y++;
            }
            y = 0;
            sample = 0;
    }
}
