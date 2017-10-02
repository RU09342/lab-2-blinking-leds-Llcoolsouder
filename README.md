# Lab 2: Blink an LED and you can control the world!
As grandiose as this statement sounds, it is fairly accurate. By the time you are done this lab, you have probably done about 75% of what makes embedded difficult. Just to blink an LED on an MSP430, you need to understand:
* The WatchDog Timer and its role in the processor
* Initialization of the Clocks
* Initialization of the GPIO
* How to set the state of a GPIO Pin
* How to implement delays
* How to poll the status of a pin
* and more...

All of this just to do something a cheap 10 cent widget from a dollar store can do; and you are going to use about $30.00 in microcontrollers to do it.

## Goals For the Lab
By the end of this lab, you will be able to:
* Initialize the WDT and Clock on the microcontroller
* Initialize and Control the GPIO on all development boards
* Blink the LED's on board the Development platforms
* Blink LED's external to the development boards
* Control the status of an LED from a Button using Polling
* Use the MSP430G2553 in a breadboard and blink LEDS without the development platform.

## Notable Differences Between Chips
For starters, all of these boards have LEDs and buttons on different pins. On one board, an LED could be on P1.0 and on another dev board the LED might be on P1.6. This accounts for most of the minute differences in the code accross boards. In some cases however you may not see a change directly in the main loop of the code if the LED or button was on a different port altogether. In this case, I defined some macros before the ```int main(void) {...}```. An example of a macro definition is show below.
```
#define LED_OUT P1OUT
```
This tells the compiler to replace all instances of LED_OUT with P1OUT. 

This allows me to change the value of the macro in one time, and leave the rest of the code the same.  No further change is necessary if the original pin in the code was _P1.x_ and the pin that I'm changing to is _P2.x_, but if I'm changing from _P1.x_ to _P2.y_ or to _P1.y_, I will need to go into the code and change which speific bits are set and cleared.  

The only other big difference that you will see in this project is the following line.

```
PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
                            // to activate previously configured port settings
```

This line is needed in order to do any kind of GPIO for the FR series chips. This line takes the pins out of high impedence mode so that you can read and write to I/O pins.
