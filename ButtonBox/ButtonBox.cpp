// Do not remove the include below
#include "ButtonBox.h"
#include "PinDefinitions.h"

#include <Encoder.h>
#include <FastSPI_LED2.h>

#include "usb_serial.h"
#include "Inputs.h"
#include "PinDefinitions.h"
#include "AbstractInteractionMode.h"
#include "ArcadeButtonTestMode.h"

bool gPluginOverrideEncoder = false;

Inputs gInputs;
InputValues gInputValues;

#define NUM_LEDS 12
CRGB gLeds[NUM_LEDS];

ArcadeButtonTestMode pArcadeButtonTestMode;

AbstractInteractionMode * gModes[] = { &pArcadeButtonTestMode };



//The setup function is called once at startup of the sketch
void setup()
{
    // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(2000);

    // For safety (to prevent too high of a power draw), the test case defaults to
    // setting brightness to 25% brightness
    LEDS.setBrightness(64);
    // Put ws2801 strip on the hardware SPI pins with a BGR ordering of rgb and limited to a 1Mhz data rate
    LEDS.addLeds<WS2801, PIN_LED_STRING_DATA, PIN_LED_STRING_CLOCK, RGB, DATA_RATE_MHZ(1)>(gLeds, NUM_LEDS);
    // Make sure our initial array is 0
    memset(gLeds, 0,  NUM_LEDS * sizeof(struct CRGB));

    //Set PIN_POWER_UP to be an output and set to high ASAP after boot.
    //NOTE: If you want to go into 'low power mode' set this pin to low. You will be shut off.
    pinMode(PIN_POWER_UP, OUTPUT);
    digitalWrite(PIN_POWER_UP, HIGH);

    //Configure all of our output pins to be outputs.
    pinMode(PIN_RED_SWITCH_LED, OUTPUT);
    pinMode(PIN_GREEN_SWITCH_LED, OUTPUT);
    pinMode(PIN_BLUE_SWITCH_LED, OUTPUT);
    pinMode(PIN_ENCODER_RED, OUTPUT);
    pinMode(PIN_ENCODER_GREEN, OUTPUT);
    pinMode(PIN_ENCODER_BLUE, OUTPUT);
    pinMode(PIN_ROUND_SWITCH_LED, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);

    //Set all of our outputs (EXCEPT POWER_UP) to be off at startup
    //NOTE: ALL of these pins should be switching on the darlington pairs w/ integrated resistors on the input to limit current draw.
    digitalWrite(PIN_RED_SWITCH_LED, LOW);
    digitalWrite(PIN_GREEN_SWITCH_LED, LOW);
    digitalWrite(PIN_BLUE_SWITCH_LED, LOW);
    digitalWrite(PIN_ENCODER_RED, LOW);
    digitalWrite(PIN_ENCODER_GREEN, LOW);
    digitalWrite(PIN_ENCODER_BLUE, LOW);
    digitalWrite(PIN_ROUND_SWITCH_LED, LOW);
    digitalWrite(PIN_BUZZER, LOW);

    //Set the rest of our pins to INPUT_PULLUP.
    //All of these inputs should switch to ground and be regarded as ACTIVE LOW.
    pinMode(PIN_BLUE_BUTTON, INPUT_PULLUP);
    pinMode(PIN_PINK_BUTTON, INPUT_PULLUP);
    pinMode(PIN_GREEN_BUTTON, INPUT_PULLUP);
    pinMode(PIN_YELLOW_BUTTON, INPUT_PULLUP);
    pinMode(PIN_RED_SWITCH, INPUT_PULLUP);
    pinMode(PIN_GREEN_SWITCH, INPUT_PULLUP);
    pinMode(PIN_MOMENTARY_LEFT, INPUT_PULLUP);
    pinMode(PIN_MOMENTARY_RIGHT, INPUT_PULLUP);
    pinMode(PIN_SWITCH_TOP, INPUT_PULLUP);
    pinMode(PIN_SWITCH_MID_TOP, INPUT_PULLUP);
    pinMode(PIN_SWITCH_MID_BOTTOM, INPUT_PULLUP);
    pinMode(PIN_SWITCH_BOTTOM, INPUT_PULLUP);
    pinMode(PIN_ROUND_SWITCH, INPUT_PULLUP);

}

// The loop function is called in an endless loop
void loop()
{
    static int lastEncoderValue = 0;
    const int numModes = 8;
    //    const int numModes = sizeof(gModes) / sizeof(AbstractInteractionMode*);
    static int currMode = 0;

    int encoderValue = gInputs.mEncoder.read();
    if ( encoderValue >= lastEncoderValue + 3 )
    {
        lastEncoderValue = encoderValue;
        currMode++;
    }
    else if ( encoderValue <= lastEncoderValue - 3 )
    {
        lastEncoderValue = encoderValue;
        currMode--;
    }

    if ( currMode >= numModes )
    {
        currMode = 0;
    }
    else if ( currMode < 0 )
    {
        currMode = numModes - 1;
    }


    for ( int offset = 0; offset < 8; ++offset )
    {
        if ( ((0x1 << offset) & currMode) )
        {
            gLeds[offset] = CRGB(128,0,128);
        }
        else
        {
            gLeds[offset] = CRGB(0,0,0);
        }
    }
    LEDS.show();

    int ledValue = encoderValue + 128;
    if ( ledValue < 0 )
    {
        ledValue = 0;
    }
    else if ( ledValue > 255 )
    {
        ledValue = 255;
    }
    analogWrite(PIN_ENCODER_RED, ledValue);

    delay(10);
}
