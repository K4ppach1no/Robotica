#include "pch.h"

#include "led.h"

#include <pigpio.h>
#include <Windows.h> //for windows sleep 

#define LED_RED 18	// Using GPIO18 for leds


void led::aan()
{
	printf("Running pigpio program\n");
	gpioInitialise(); // you MUST initialize the library !

	//gpiowrite >> digital write
	//gpioPWM >> analog write

 		/* for the pins
		

You set the mode (normally PI_INPUT or PI_OUTPUT) with gpioSetMode.

You set the level (PI_LOW or PI_HIGH) with gpioWrite.
*/
}
