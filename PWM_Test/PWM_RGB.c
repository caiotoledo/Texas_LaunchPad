/*
 * PWM_RGB.c
 *
 *  Created on: 14/05/2016
 *      Author: Caio
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "PWM_RGB.h"

void LED_init(LED_RGB led, uint32_t period, uint32_t duty){
	uint32_t GPIOPinConf;
	uint32_t GPIOPinType;
	uint32_t PWMGen;
	uint32_t PWMOut;
	uint32_t PWMOutBit;

	switch (led) {
		case RED_LED:
			GPIOPinConf = GPIO_PF1_M1PWM5;
			GPIOPinType = GPIO_PIN_1;
			PWMGen = PWM_GEN_2;
			PWMOut = PWM_OUT_5;
			PWMOutBit = PWM_OUT_5_BIT;
			break;
		case BLUE_LED:
			GPIOPinConf = GPIO_PF2_M1PWM6;
			GPIOPinType = GPIO_PIN_2;
			PWMGen = PWM_GEN_3;
			PWMOut = PWM_OUT_6;
			PWMOutBit = PWM_OUT_6_BIT;
			break;
		case GREEN_LED:
			GPIOPinConf = GPIO_PF3_M1PWM7;
			GPIOPinType = GPIO_PIN_3;
			PWMGen = PWM_GEN_3;
			PWMOut = PWM_OUT_7;
			PWMOutBit = PWM_OUT_7_BIT;
			break;
		default:
		//If the Value is wrong, stop the configuration:
			return;
	}

	if (duty > WIDTH_BASE) {
		duty = WIDTH_BASE;
	}

	SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

	GPIOPinConfigure(GPIOPinConf);

	GPIOPinTypePWM(GPIO_PORTF_BASE, GPIOPinType);

	PWMGenConfigure(PWM1_BASE, PWMGen, PWM_GEN_MODE_UP_DOWN|PWM_GEN_MODE_NO_SYNC);

	PWMGenPeriodSet(PWM1_BASE, PWMGen, period);

	uint32_t base = period*duty/WIDTH_BASE;

	PWMPulseWidthSet(PWM1_BASE, PWMOut, base);

	PWMOutputState(PWM1_BASE, PWMOutBit, true);

	PWMGenEnable(PWM1_BASE, PWMGen);

	PWMOutputInvert(PWM1_BASE, PWMOutBit, false);
}

void setLedDuty (LED_RGB led, uint32_t duty){
	uint32_t base;
	uint32_t PWMOut;
	uint32_t PWMGen;

	switch (led) {
		case RED_LED:
			PWMOut = PWM_OUT_5;
			PWMGen = PWM_GEN_2;
			break;
		case BLUE_LED:
			PWMOut = PWM_OUT_6;
			PWMGen = PWM_GEN_3;
			break;
		case GREEN_LED:
			PWMOut = PWM_OUT_7;
			PWMGen = PWM_GEN_3;
			break;
		default:
			return;
	}

	base = PWMGenPeriodGet(PWM1_BASE, PWMGen)*duty/WIDTH_BASE;

	PWMPulseWidthSet(PWM1_BASE, PWMOut, base);
}

void setRGB(uint32_t rValue, uint32_t gValue, uint32_t bValue){

	if (rValue > WIDTH_BASE) {
		rValue = WIDTH_BASE;
	}
	if (gValue > WIDTH_BASE) {
		gValue = WIDTH_BASE;
	}
	if (bValue > WIDTH_BASE) {
		bValue = WIDTH_BASE;
	}

	setLedDuty(RED_LED, rValue);
	setLedDuty(GREEN_LED, gValue);
	setLedDuty(BLUE_LED, bValue);
}
