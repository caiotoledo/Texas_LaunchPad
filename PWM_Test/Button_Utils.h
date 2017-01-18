/*
 * GPIO_Utils.h
 *
 *  Created on: 14/01/2017
 *      Author: Caio
 */

#ifndef GPIO_UTILS_H_
#define GPIO_UTILS_H_

enum eButtonPin {
	ButtonSW1,
	ButtonSW2,
};

enum eButtonState {
	stateOn = 0,
	stateOff = 1,
	Error = 100,
};

typedef enum eButtonPin ButtonPin;
typedef enum eButtonState ButtonState;

void Button_init(void);
ButtonState ButtonRead(ButtonPin bButton);

#endif /* GPIO_UTILS_H_ */
