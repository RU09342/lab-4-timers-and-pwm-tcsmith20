# Hardware PWM
Now that we have learned about GPIO ports, timers and interrupts, about 80% of embedded systems has been learned. This lab aims to put all newly gained skills to the test by using a mix of GPIO, timers and interrupts. The second excercise consists of creating Pulse Width Modulation (PWM) using software. 

## PWM
Dealing with digital signals, a signal can only be high (3.3 V) or low (0 V). The proportion of time the signal is high compared to when it is low over a consistent frequency is Pulse Width Modulation.

![alt text](https://github.com/RU09342/lab-4-timers-and-pwm-tcsmith20/blob/master/Hardware%20PWM/HW%20PWM.gif) 

## How Does The Code Work
Using the MSP430 library I created, it was easy to implement all five required processors into one main.c file. The main method disables the watchdog timer, initializes the processors setup, LEDs, button 1 and Timer A (This is all done through the Library). Usually, Timer A interrupts would be enabled. However, the purpose of the hardware interrupt is to directly output the Timer to an LED. I created a hal_pwm.h file just for this lab to initialize any port directions, select registers or timer controls needed for each specific processor. This file can be found in this excercises MSP Library. These files are project specific and will most likely not be used in future labs. Button 1 and Timer B interrupts were used for incrementing duty cycle and debouncing like the previous excercises.


## Important Things to Note
* Outputting a timer to a GPIO pin is not as trivial as it seems. Each processor varies greatly on register names and restrictions. Some processors could only output to one LED, not both. Other times, only specific timers could be used. All of these specifications can be found in a data table in each processor specific datasheet.