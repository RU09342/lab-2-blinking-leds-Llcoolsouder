# Multiple Blink
This is the code for blinking 2 LEDs at 2 different rates. As a band geek, I like cool timing things so my LEDs emulate a duple over triple feel. In mathematic terms, for every 2 blinks on one LED there will be exactly 3 blinks on the other LED. The exact code below is the specific code to do this on the MSP430G2553. 

```
#include <msp430.h> 

#define LED1_OUT P1OUT
#define LED1_DIR P1DIR
#define LED2_OUT P1OUT
#define LED2_DIR P1DIR


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    LED1_DIR |= BIT0;           // Set LED to output
    LED1_OUT &= ~BIT0;          // Initialize LED to OFF
    LED2_DIR |= BIT6;           // Set LED to output
    LED2_OUT |= BIT6;           // Initialize LED to ON

    while (1){
        LED1_OUT ^= BIT0;       //Toggle LED
        LED2_OUT ^= BIT6;       //Toggle LED
        __delay_cycles(200000);
        LED1_OUT ^= BIT0;       //Toggle LED
        __delay_cycles(100000);
        LED2_OUT ^= BIT6;       //Toggle LED
        __delay_cycles(100000);
        LED1_OUT ^= BIT0;       //Toggle LED
        __delay_cycles(200000);
    }
}
```

The code for this is almost identical to the code for the [Simple Blink](https://github.com/RU09342/lab-2-blinking-leds-Llcoolsouder/tree/master/Simple%20Blink). The only difference is there are more delays and toggles for each iteration of the while loop.
