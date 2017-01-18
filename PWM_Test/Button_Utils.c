/*
 * GPIO_Utils.c
 *
 *  Created on: 14/01/2017
 *      Author: Caio
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "Button_Utils.h"

void Button_init(void){

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //
    // Unlock PF0 so we can change it to a GPIO input
    // Once we have enabled (unlocked) the commit register then re-lock it
    // to prevent further changes.  PF0 is muxed with NMI thus a special case.
    //
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;

    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_DIR_MODE_IN);

    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

}

ButtonState ButtonRead(ButtonPin bButton){

	uint32_t port;
	uint8_t pin;

	uint32_t gpioRead;

	ButtonState bState;

	switch (bButton) {
		case ButtonSW1:
			port = GPIO_PORTF_BASE;
			pin = GPIO_PIN_4;
			break;
		case ButtonSW2:
			port = GPIO_PORTF_BASE;
			pin = GPIO_PIN_0;
			break;
		default:
			return Error;
	}

	gpioRead = GPIOPinRead(port, pin);
	if (!gpioRead) {
		SysCtlDelay(80000);
		gpioRead = GPIOPinRead(port, pin);
	}

	if (gpioRead) {
		bState = stateOff;
	} else {
		bState = stateOn;
	}

	return bState;
}
