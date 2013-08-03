// Do not remove the include below
#include <FastSPI_LED2.h>
#include "TestWS2801.h"

#define NUM_LEDS 12

CRGB leds[NUM_LEDS];

//The setup function is called once at startup of the sketch
void setup()
{
	// sanity check delay - allows reprogramming if accidently blowing power w/leds
   	delay(2000);

   	// For safety (to prevent too high of a power draw), the test case defaults to
   	// setting brightness to 25% brightness
   	LEDS.setBrightness(64);

	// Put ws2801 strip on the hardware SPI pins with a BGR ordering of rgb and limited to a 1Mhz data rate
	LEDS.addLeds<WS2801, 11, 13, RGB, DATA_RATE_MHZ(1)>(leds, NUM_LEDS);
}

// The loop function is called in an endless loop
void loop()
{
	for(int i = 0; i < 3; i++)
	{
		for(int iLed = 0; iLed < NUM_LEDS; iLed++)
		{
			memset(leds, 0,  NUM_LEDS * sizeof(struct CRGB));

			switch(i) {
				// You can access the rgb values by field r, g, b
			 	case 0: leds[iLed].r = 128; break;

			 	// or by indexing into the led (r==0, g==1, b==2)
			 	case 1: leds[iLed][i] = 128; break;

			 	// or by setting the rgb values for the pixel all at once
			 	case 2: leds[iLed] = CRGB(0, 0, 128); break;
			}

			// and now, show your led array!
			LEDS.show();
			delay(10);
		}

		// fade up
		for(int x = 0; x < 128; x++)
		{
			// The showColor method sets all the leds in the strip to the same color
			LEDS.showColor(CRGB(x, 0, 0));
			delay(10);
		}

		// fade down
		for(int x = 128; x >= 0; x--)
		{
			LEDS.showColor(CRGB(x, 0, 0));
			delay(10);
		}

		// let's fade up by scaling the brightness
		for(int scale = 0; scale < 128; scale++)
		{
			LEDS.showColor(CRGB(0, 128, 0), scale);
			delay(10);
		}

		// let's fade down by scaling the brightness
		for(int scale = 128; scale > 0; scale--)
		{
			LEDS.showColor(CRGB(0, 128, 0), scale);
			delay(10);
		}
	}
}
