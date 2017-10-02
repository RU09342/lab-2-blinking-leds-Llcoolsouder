# Simple Blink
The simple blink code simply toggles an LED on and off with some delay in between. The code basically looks like this for each board (this is the specific code for the MSP430G2553).

```
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
```
## Register Info
The important registers for this code are _PxDIR_ and _PxOUT_. In reality there are other registers that could have (and probably should have) been included here, but it turns out they are set to what I need by default. _PxDIR_ sets the direction of a GPIO pin in _Port X_. Setting this HIGH sets the pin to __output__. Setting this LOW, sets the pin to __input__. _PxOUT_ sets the output of the pin. As you would expect, setting this HIGH turns the pin HIGH, while setting this LOW, turns the pin LOW.  

## Bit Setting/Clearing
The MSP430 has 8-bit ports, which means when you operate on Port1, you're not operating on a single pin; you're operating on all 8. There are some ways around this however. To manipulate these registers, we use bitwise operations and masks, to set or clear the bit we want without touching the other bits. 
In order to __set__ a bit we use _bitwise OR_ with a mask containing a 1 only in the bit we wish to set. For instance,
```
P1OUT |= BIT0;
```
or
```
P1OUT |= 0x0001;
```
will both set bit 0 of P1OUT.
To __clear__ a bit we use _bitwise AND_ with a mask containing a 0 only in the bit we wish to clear. For instance,
```
P1OUT &= ~BIT2;
```
or
```
P1OUT &= ~0x00004; 
```
will both clear bit 2 of P1OUT;
To __toggle__ a bit we use _bitwise XOR_ with a mask containing a 1 only in the bit we want to toggle. For instance,
```
P1OUT ^= BIT1;
```
will toggle bit 1 of P1OUT. If bit1 is currently a 1, then it will become a 0 because 1^1==0, but if it is currently a 0, then it will become a 1 because 1^0==1.

## Delays
Delays can be done in a number of ways. In this code, I used ```__delay_cycles()``` which take an integer literal and basically inserts NOPs into the program until the processor has delayed enough cycles.  I chose this function because it's a simple one line fix for a simple task. In other parts of this lab, I will use one different approach to delays.
