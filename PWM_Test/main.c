#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "PWM_RGB.h"

#define	COLOR_FACTOR	10
#define COLOR_MIN		16
#define COLOR_MAX		223

int main(void) {
	SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_XTAL_16MHZ |
	SYSCTL_OSC_MAIN);

	uint32_t state = 0;

	uint32_t rColor = COLOR_MAX;
	uint32_t gColor = COLOR_MIN;
	uint32_t bColor = COLOR_MIN;

	LED_init(RED_LED, 64000, rColor);
	LED_init(BLUE_LED, 64000, gColor);
	LED_init(GREEN_LED, 64000, bColor);

	while (1){
		SysCtlDelay(600000);

		switch (state) {
			case 0:
				bColor += COLOR_FACTOR;
				if (bColor > COLOR_MAX) {
					state++;
					bColor = COLOR_MAX;
				}
				break;
			case 1:
				rColor -= COLOR_FACTOR;
				if (rColor > COLOR_MAX) {
					state++;
					rColor = COLOR_MIN;
				}
				break;
			case 2:
				gColor += COLOR_FACTOR;
				if (gColor > COLOR_MAX) {
					state++;
					gColor = COLOR_MAX;
				}
				break;
			case 3:
				bColor -= COLOR_FACTOR;
				if (bColor > COLOR_MAX) {
					state++;
					bColor = COLOR_MIN;
				}
				break;
			case 4:
				rColor += COLOR_FACTOR;
				if (rColor > COLOR_MAX) {
					rColor = COLOR_MAX;
					state++;
				}
			case 5:
				gColor -= COLOR_FACTOR;
				if (gColor > WIDTH_BASE) {
					gColor = COLOR_MIN;
					state = 0;
				}
				break;
			default:
				state = 0;
				rColor = WIDTH_BASE;
				gColor = 0;
				bColor = 0;
				break;
		}
		setRGB(rColor, gColor, bColor);
	}
}
