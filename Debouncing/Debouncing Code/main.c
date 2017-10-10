#include <msp430.h>
#include "Tanner's MSP Lib/setup/setup.h"
#include "Tanner's MSP Lib/led/led.h"
#include "Tanner's MSP Lib/button/button.h"
#include "Tanner's MSP Lib/timer/timer.h"

unsigned int pull_up = 1;
unsigned int neg_edge_trigger = 1;

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;                   // Stop watchdog timer
    Setup_Init();                               // Turn off High Impedance for GPIO

    Led1_Init();                                // Initialize Led1
    Led1_Off();                                 // Turn off Led1
    Led2_Init();                                // Initialize Led2
    Led2_On();                                  // Turn on Led2

    Button1_Init(pull_up);                      // Initialize button to pull up resistor
    Button1_EnableInterrupt(neg_edge_trigger);  // Enable the interrupt for negative edge triggers

    __bis_SR_register(LPM0_bits + GIE);       // Enter LPM4 w/interrupt

    while(1){

    }
}

void Button1_ISR(){
    if(neg_edge_trigger){                       // If the button is pressed or depressed
        Led1_Toggle();                          // Toggle Led 1
        Led2_Toggle();                          // Toggle Led 2
    }
    TimerA_Init(SMCLK, UP, DIV8, 3000);         // Initialize clock for short period of time
    TimerA_EnableInterrupt0();                  // Enable the clock interrupt
    Button1_DisableInterrupt();                 // Disable the button interrupt until the timer stops to prevent debouncing
    Button1_ClearFlag();                        // Clear the button interrupt flag
}

void TimerA_ISR(){
    if(neg_edge_trigger){                               // If neg edge trigger
        neg_edge_trigger = 0;                           // Change to pos edge trigger
        Button1_EnableInterrupt(neg_edge_trigger);      // Enable Interrupt on pos edge
    }
    else{                                               // If pos edge trigger
        neg_edge_trigger = 1;                           // Change to neg edge
        Button1_EnableInterrupt(neg_edge_trigger);      // Enable interrupt on neg edge
    }
    TimerA_Stop();          // Stop the timer until the button is pressed again.
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

/** ALL TIMER A INTERRUPT ROUTINES FOR 5 PROCESSORS */

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void){
    TimerA_ISR();
}

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B (void){
    TimerA_ISR();
}
