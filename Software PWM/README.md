# Software PWM
Now that we have learned about GPIO ports, timers and interrupts, about 80% of embedded systems has been learned. This lab aims to put all newly gained skills to the test by using a mix of GPIO, timers and interrupts. The second excercise consists of creating Pulse Width Modulation (PWM) using software. 

![alt text](https://github.com/RU09342/lab-4-timers-and-pwm-tcsmith20/blob/master/Software%20PWM/SW%20PWM.gif)

## How Does The Code Work
Using the MSP430 library I created, it was easy to implement all five required processors into one main.c file. The main method disables the watchdog timer, initializes the processors setup, LEDs, button 1 and Timer B (This is all done through the Library). Timer B will used as the PWM timer. Timer B was initialized to use the SMCLK (1 MHz), up mode, no divider and a CCR0 value of 1000. Since Timer B is in up mode and CCR0 is 1000, the CCR0 interrupt will fire at 1 kHz. CCR1 is then set to the ratio of on time to total time (duty cycle).  For example, if the duty cycle was 50%, CCR1 would be set to 500 since CCR0 is set to 1000. When the button 1 interrupt is fired, the duty cycle increments by 10 and Timer A is used for debouncing purposes.


## Important Things to Note
* Many, many timer interrupts are used in this code. One is used to help debouncing, one is fired when the PWM timer overflows and the other fires depending on the duty cycle. It is very important to keep track of which timer and interrupt is doing. Don't forget to properly name your interrupt vectors.