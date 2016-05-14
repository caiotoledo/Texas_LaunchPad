/*
 * PWM_RGB.h
 *
 *  Created on: 14/05/2016
 *      Author: Caio
 */

#ifndef PWM_RGB_H_
#define PWM_RGB_H_

#define WIDTH_BASE	255

enum eLED_RGB {
	RED_LED,
	BLUE_LED,
	GREEN_LED,
};

typedef enum eLED_RGB LED_RGB;

void LED_init(LED_RGB led, uint32_t period, uint32_t duty);
void setLedDuty (LED_RGB led, uint32_t duty);
//void setRGB(uint32_t valueRGB);
void setRGB(uint32_t rValue, uint32_t gValue, uint32_t bValue);

#endif /* PWM_RGB_H_ */
