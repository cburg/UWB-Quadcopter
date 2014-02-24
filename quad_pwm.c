

#include "quad_common.h"
#include "quad_pwm.h"

void quad_pwm_init() {
	// Motor 1: Port D Pin 0 (PD0)
	// Motor 2: Port D Pin 1 (PD1)
	// Motor 3: Port A Pin 6 (PA6)
	// Motor 4: Port A Pin 7 (PA7)
	// Red LED: Port F Pin 1 (PF1)
	// Blu LED: Port F Pin 2 (PF2)
	// Grn LED: Port F Pin 3 (PF3)

	// Set the clock for the PWM and global variables
	SysCtlPWMClockSet(SYSCTL_PWMDIV_32);
	
	
	pwm1_clock_freq_hz = SysCtlClockGet() / 32;
	pwm1_period_len_us = PWM1_PERIOD_us;
	pwm1_period_num_ticks = (pwm1_clock_freq_hz * PWM1_PERIOD_us) / 
							(PWM1_TIME_RES_Hz);
	
	
	
	// Enable the peripheral devices / ports
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);	// Motors 3 and 4
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);	// Motors 1 and 2
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);	// for the RGB LED
	
	
	
	// Set the pins on the aformentioned ports
	GPIOPinTypePWM(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7); // motors 3 and 4
	GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1); // motors 1 and 2
	GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); // for the RGB LED
	
	GPIOPinConfigure(GPIO_PD0_M1PWM0);	// motor 1
	GPIOPinConfigure(GPIO_PD1_M1PWM1);	// motor 2
	GPIOPinConfigure(GPIO_PA6_M1PWM2);	// motor 3
	GPIOPinConfigure(GPIO_PA7_M1PWM3);	// motor 4
	GPIOPinConfigure(GPIO_PF1_M1PWM5);	// red led
	GPIOPinConfigure(GPIO_PF2_M1PWM6);	// blue led
	GPIOPinConfigure(GPIO_PF3_M1PWM7);	// green led
	
	
	
	// Set the PWM Generators and periods, and calculate numbers of ticks
	PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
	PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
	PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
	PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
	
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, pwm1_period_num_ticks);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, pwm1_period_num_ticks);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, pwm1_period_num_ticks);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, pwm1_period_num_ticks);
	
	
	
	// Enable PWM output
	PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true); // motor 1
	PWMOutputState(PWM1_BASE, PWM_OUT_1_BIT, true); // motor 2
	PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true); // motor 3
	PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, true); // motor 4
	PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true); // red led
	PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true); // blue led
	PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true); // green led
	
	PWMGenEnable(PWM1_BASE, PWM_GEN_0);
	PWMGenEnable(PWM1_BASE, PWM_GEN_1);
	PWMGenEnable(PWM1_BASE, PWM_GEN_2);
	PWMGenEnable(PWM1_BASE, PWM_GEN_3);
	

}
