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

#define BTN_RES P5REN
#define BTN_DIR P5DIR
#define BTN_IN  P5IN



int main(void)

{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
                                // to activate previously configured port settings

    P1SEL0 &= ~BIT0;            // Set P1.0 (LED) to GPIO
    P1SEL1 &= ~BIT0;
    P5SEL0 &= ~BIT6;            // SET P5.6 (Button) to GPIO
    P5SEL1 &= ~BIT6;

    LED_DIR |= BIT0;            // Set LED to output
    LED_OUT |= BIT0;            // Initialize LED to ON

    BTN_DIR &= ~BIT6;           // Set Button as input

    P5OUT |= BIT6;              // Turn on pullup resistor
    BTN_RES |= BIT6;


    unsigned x = 0;
    unsigned y = 0;
    unsigned count = 0;
    float sample = 0;
    unsigned i = 0;
    while (1) {
        for (i = 1000; i>0; i--) {
            if (!(BTN_IN & BIT6))
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
                if (!(BTN_IN & BIT6))
                    break;
                y++;
            }
            y = 0;
            sample = 0;
    }
    /*
    int delay;
    while (1){
        while (!(BTN_IN & BIT6)){   // if button is pushed
            delay = 0;
            LED_OUT ^= BIT0;        // Toggle LED
            while (delay<10000){    // if button is released
                 if (BTN_IN & BIT6)
                     break;         // Break out of
                 else
                     delay++;
            }
        }
        LED_OUT &= ~BIT0;
    }
    */
}
