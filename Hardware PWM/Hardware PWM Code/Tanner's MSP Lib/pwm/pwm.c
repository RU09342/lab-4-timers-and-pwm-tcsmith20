/*
 * pwm.c
 *
 *  Created on: Oct 9, 2017
 *      Author: Tanner
 */

#include "hal_pwm.h"
#include "pwm.h"


void PWM_Init(){

    *led_dir_reg |= led_position;
    *led_sel_reg |= led_position;
    *led_sel2_reg = sel2_val;
    *timer_ctl_reg |= timer_mode;

}
