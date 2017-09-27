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
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    P1SEL &= ~(BIT1 | BIT0);    // Set P1.1 (Button) and P1.0 (LED) to GPIO

    LED_DIR |= BIT0;            // Set LED to output
    LED_OUT |= BIT0;            // Initialize LED to ON

    BTN_DIR &= ~BIT1;           // Set Button as input

    P1OUT |= BIT1;              // Turn on pullup resistor
    BTN_RES |= BIT1;

    unsigned x = 0;
    unsigned y = 0;
    unsigned count = 0;
    float sample = 0;
    unsigned i = 0;
    while (1) {
        for (i = 1000; i>0; i--) {
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
}
