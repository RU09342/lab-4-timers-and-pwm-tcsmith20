/*
 * hal_pwm.h
 *
 *  Created on: Oct 9, 2017
 *      Author: Tanner
 */

#ifndef HAL_PWM_H_
#define HAL_PWM_H_

/** Assigns register pointers to variables depending on target specified processor */
#if defined(__MSP430G2553__)
    #include <msp430g2553.h>

    volatile unsigned char * led_dir_reg =        &P1DIR;
    volatile unsigned char * led_sel_reg =        &P1SEL;
    volatile unsigned char * led_sel2_reg =       &P1SEL2;
    volatile unsigned int  * timer_ctl_reg =      &TA0CCTL1;

    int led_position =                           BIT6;
    int sel2_val =                               0;
    int timer_mode =                             OUTMOD_7;

#elif defined(__MSP430FR5994__)
    #include <msp430fr5994.h>

    volatile unsigned char * led_dir_reg =        &P1DIR;
    volatile unsigned char * led_sel_reg =        &P1SEL0;
    volatile unsigned char * led_sel2_reg =       &P1SEL1;
    volatile unsigned int  * timer_ctl_reg =      &TA0CCTL1;

    int led_position =                           BIT1;
    int sel2_val =                               0;
    int timer_mode =                             OUTMOD_7;

#elif defined(__MSP430FR2311__)
    #include <msp430fr2311.h>

    volatile unsigned char * led_dir_reg =        &P2DIR;
    volatile unsigned char * led_sel_reg =        &P2SEL0;
    volatile unsigned char * led_sel2_reg =       0;
    volatile unsigned int  * timer_ctl_reg =      &TB1CCTL1;

    int led_position =                           BIT0;
    int sel2_val =                               0;
    int timer_mode =                             OUTMOD_7;

#elif defined(__MSP430F5529__)
    #include <msp430f5529.h>

    volatile unsigned char * led_dir_reg =        &P1DIR;
    volatile unsigned char * led_sel_reg =        &P1SEL;
    volatile unsigned char * led_sel2_reg =       0;
    volatile unsigned int  * timer_ctl_reg =      &TA0CCTL1;

    int led_position =                           BIT0;
    int sel2_val =                               0;
    int timer_mode =                             OUTMOD_7;


#elif defined(__MSP430FR6989__)
    #include <msp430fr6989.h>

    volatile unsigned char * led_dir_reg =        &P1DIR;
    volatile unsigned char * led_sel_reg =        &P1SEL0;
    volatile unsigned char * led_sel2_reg =       &P1SEL1;
    volatile unsigned int  * timer_ctl_reg =      &TA0CCTL1;

    int led_position =                           BIT0;
    int sel2_val =                               0;
    int timer_mode =                             OUTMOD_7;

#endif



#endif /* TANNER_S_MSP_LIB_PWM_HAL_PWM_H_ */
