# Button Blink
This code uses a button as input to control an LED. The specific code shown below is from the MSP430FR2311.

## Simple Switch
The code below is one of the most general cases in which a button might be used for input to a microprocessor. When this code is run, the following behavior will be observed. When the button is pushed, the  LED should blink. When the button is released, the LED should stop blinking immediately (or very close to immediately). The setup code (everything before the first while loop) is nothing that you shouldn't have seen in [Simple Blink](https://github.com/RU09342/lab-2-blinking-leds-Llcoolsouder/tree/master/Simple%20Blink) or [Multiple Blink](https://github.com/RU09342/lab-2-blinking-leds-Llcoolsouder/tree/master/Multiple%20Blink). The main difference you will observe in this code as a result of responding to an input is _polling_.
```
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
    LED_OUT |= 0x0001;          // Initialize LED to ON

    BTN_DIR &= ~0x0002;         // Set Button as input
    BTN_RES |= 0x0002;          // Turn on pullup resistor

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
}
```
### Polling
_Polling_ is a technique used to check for input in a processor. This is considered the worst method of handling inputs because it requires the processor to constantly check the state of an input. This is very computation intensive and it consumes more power than its alternatives (which will be discussed in [Lab 3](https://github.com/RU09342/lab-3-interrupts-and-timers-Llcoolsouder)). For now though, this is the easiest solution to implement as it is easy to understand what the processor is actually doing. In the code above, you will notice the while loop, ```while(!(BTN_IN & BIT0)) {...}```. What this does is check whether or not _bit 0_ of BTN\_IN (defined as P1IN) is HIGH every time this code is reached. If the button is not pushed, then ```BTN_IN & BIT0``` will evaluate to 0x0001 which is considered TRUE by the C compiler. If the button is pushed, then ```BTN_IN & BIT0``` will evaluate to 0x0000 which is considered FALSE by the C compiler. The ```!``` in front inverts the boolean value, so that the while loop executes when the button is pushed.

### Breaking a Delay
Once inside the while loop, I have implemented a different kind of delay than the one used in [Simple Blink](https://github.com/RU09342/lab-2-blinking-leds-Llcoolsouder/tree/master/Simple%20Blink) or [Multiple Blink](https://github.com/RU09342/lab-2-blinking-leds-Llcoolsouder/tree/master/Multiple%20Blink). Using ```__delay_cycles(const unsigned int)``` will delay the processor, but what if something occurs during the delay which takes priority? In this case you will want a way to break out of the delay. The implementation for this uses a while loop that continually checks for a particular change in state (_polling_ once again) and breaks the loop and thus the delay if the state change is detected. Otherwise, it increments a counter until it hits the desired number in which case it will also terminate the loop. Unfortunately, this method does not yield an accurate or easily predictable number of delayed cycles because it requires more than just one simple NOP for each iteration of the loop, so setting the loop to break when ```delay<10000``` will not result in a 10000 cycle max delay. It could be much more.

```
while (delay<10000){    
  if (BTN_IN & BIT1)    // if button is released
    break;              // Break out of
  else
    delay++;
}
```
            


## State Changes
The code below can be used to replace the loop in the above code in order to use the button to control state changes.  The behavior should be as follows. On startup, the LED should be on. When the button is pushed, the LED should begin to blink. For each button push thereafter, the LED should cycle through 3 different blinking frequencies. This code also implements a software debouncer.

```
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
```

### Debouncing
The problem of button bouncing lies in the fact that mechanical devices are inherently flawed. In the case of buttons, they have a spring-like property which causes them to oscillate when released.  The microprocessor picks up this oscillation as multiple button pushes. In order to get rid of this problem, I implemented a system that samples the button input and takes an average of the signal over some time interval. If most of the samples were HIGH, then it reads the signal as HIGH overall. If most of the samples were LOW, then it reads the signal as LOW overall. Notice that ```sample``` is a ```float``` so that the average can actually be between 1 and 0.

```
float sample = 0;
for (i = 1000; i>0; i--) {
    if (!(BTN_IN & BIT1))
        sample++;
}
if (sample/500 > 0.5) {...}
```
