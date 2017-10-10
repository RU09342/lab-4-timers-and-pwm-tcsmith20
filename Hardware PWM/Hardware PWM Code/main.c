#include <msp430g2553.h>
#include "Tanner's MSP Lib/setup/setup.h"
#include "Tanner's MSP Lib/led/led.h"
#include "Tanner's MSP Lib/button/button.h"
#include "Tanner's MSP Lib/timer/timer.h"
#include "Tanner's MSP Lib/pwm/pwm.h"

unsigned int pull_up = 1;
unsigned int neg_edge_trigger = 1;
unsigned int duty_cycle = 50;

/**
 * main.c
 */
int main(void){

    WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer

    Setup_Init();                               // Turn off High Impedance for GPIO pins

    Led1_Init();                                // Initialize Led1
    Led1_Off();                                 // Turn off Led1
    Led2_Init();                                // Initialize Led2
    Led2_Off();                                 // Turn off Led2

    Button1_Init(pull_up);                      // Initialize button 1 with pul up resistor
    Button1_EnableInterrupt(neg_edge_trigger);  // Enable initial interrupt on neg edge trigger

    TimerA_Init(SMCLK, UP, DIV1, 1000);         // Initialize Timer B as PWM timer (1 MHz, up mode)
    TimerA_SetCompareVal1(duty_cycle * 10);     // Set CCR1 to the duty_cycle times 10 (Since CCR0 is 1000)

    PWM_Init();

    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM4 w/interrupt

}

void Button1_ISR(){
    Led1_Toggle();                 // When button is pressed or depressed, toggle LED1

    if(neg_edge_trigger){           // If pressed down
        duty_cycle += 10;           // Increment duty cycle by 10
        if(duty_cycle > 100){       // If duty cycle is greater than 100
            duty_cycle = 0;         // Reset duty cycle to zero
        }
        TimerA_SetCompareVal1(duty_cycle * 10); // Change CCR1 to new duty cycle
    }

    TimerB_Init(SMCLK, UP, DIV8, 3000);     // Initialize debounce timer
    TimerB_EnableInterrupt0();              // Enable debounce intterupts
    Button1_DisableInterrupt();             // Disable button interrupts for debouncing
    Button1_ClearFlag();                    // Clear button 1 flag
}

void TimerB_CCR0_ISR(){
    if(neg_edge_trigger){                           // If neg edge trigger
        neg_edge_trigger = 0;                       // Flip trigger edge
        Button1_EnableInterrupt(neg_edge_trigger);  // Enable interrupt for new edge trigger
    }
    else{                                           // If pos edge trigger
        neg_edge_trigger = 1;                       // Flip trigger edge
        Button1_EnableInterrupt(neg_edge_trigger);  // Enable interrupt for new edge
    }
    TimerB_Stop();                                  // Stop and reset debounce timer for next button press
}


/** ALL BUTTON1 INTERRUPT ROUTINES FOR 5 PROCESSORS */

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void) {
    Button1_ISR();
}

#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void) {
    Button1_ISR();
}

#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void) {
    Button1_ISR();
}

/** ALL TIMER B CCR 0 INTERRUPT ROUTINES FOR 5 PROCESSORS */

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0 (void){
    TimerB_CCR0_ISR();
}

#pragma vector=TIMER1_B0_VECTOR
__interrupt void Timer1_B0 (void){
    TimerB_CCR0_ISR();
}
