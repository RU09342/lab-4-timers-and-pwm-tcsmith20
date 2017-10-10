# Software Debouncing
Now that we have learned about GPIO ports, timers and interrupts, about 80% of embedded systems has been learned. This lab aims to put all the newly gained skills to the test by using a mix of GPIO, timers and interrupts. The first excercise consists of solving debouncing using software. Bouncing is when a mechanical switch bounces when pressed causing multiple undesired edges. 

![alt text](https://github.com/RU09342/lab-4-timers-and-pwm-tcsmith20/blob/master/Debouncing/Debouncing.gif)

## How Does The Code Work
Using the MSP430 library I created, it was easy to implement all five required processors into one main.c file. The main method disables the watchdog timer, initializes the processors setup, LEDs, button 1 and Timer A (This is all done through the Library). Button 1's interrupt is initially enabled to trigger on the negative edge but the code switches the edge every time the button is pressed. When the button interrupt is fired, the ISR checks to see which edge caused the interrupt. The LEDs only toggle on the negative edge. Then, regardless of edge, Timer A is initialized to use SMCLK, a divider of 8, up mode and a CCR0 value of 3000. These values can vary since they are only used to delay the next button interrupt. Then Timer A's interrupt is enabled and button 1's interrupt is disabled and flag is cleared. Timer A then counts until CCR0. When the interrupt fires, button 1's interrupt will reenable on the opposite edge it was previously. Timer A is then stopped and reset for the next button press.


## Important Things to Note
* Originally, debouncing was only implemented when the button was pressed down (neg edge) because this is when switch bouncing is most likely to happen. However, when the button was released, the state of the LEDs varied from what was expected. This problem was fixed when debouncing was implemented on both edge triggers.
