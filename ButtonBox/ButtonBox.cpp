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
#include "RgbEncoderActions.h"

bool gPluginOverrideEncoder = false;

Inputs gInputs;
InputValues gInputValues;

CRGB gLeds[NUM_LEDS];

ArcadeButtonTestMode pArcadeButtonTestMode;
RgbEncoderActions pRgbEncoderActions;

AbstractInteractionMode * gPlugins[] = { &pArcadeButtonTestMode, &pRgbEncoderActions };
const int gNumPlugins = sizeof(gPlugins) / sizeof(AbstractInteractionMode*);

//The setup function is called once at startup of the sketch
void setup()
{
    // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(2000);

    // For safety (to prevent too high of a power draw), the test case defaults to
    // setting brightness to 25% brightness
    LEDS.setBrightness(32);
    // Put ws2801 strip on the hardware SPI pins with a BGR ordering of rgb and limited to a 1Mhz data rate
    LEDS.addLeds<WS2801, PIN_LED_STRING_DATA, PIN_LED_STRING_CLOCK, RGB, DATA_RATE_MHZ(1)>(gLeds, NUM_LEDS);
    // Make sure our initial array is 0
    memset(gLeds, 0,  NUM_LEDS * sizeof(struct CRGB));

    //Set PIN_LED_POWER_UP to be an output and set to high ASAP after boot.
    //NOTE: If you want to go into 'low power mode' set this pin to low. The LEDs will be shut off (~9mA saved).
    pinMode(PIN_LED_POWER_UP, OUTPUT);
    digitalWrite(PIN_LED_POWER_UP, HIGH);

    //Configure all of our output pins to be outputs.
    pinMode(PIN_RED_SWITCH_LED, OUTPUT);
    pinMode(PIN_GREEN_SWITCH_LED, OUTPUT);
    pinMode(PIN_BLUE_SWITCH_LED, OUTPUT);
    pinMode(PIN_ENCODER_RED, OUTPUT);
    pinMode(PIN_ENCODER_GREEN, OUTPUT);
    pinMode(PIN_ENCODER_BLUE, OUTPUT);
    pinMode(PIN_BUZZER, OUTPUT);

    //Set all of our outputs (EXCEPT POWER_UP) to be off at startup
    //NOTE: ALL of these pins should be switching on the darlington pairs w/ integrated resistors on the input to limit current draw.
    digitalWrite(PIN_RED_SWITCH_LED, LOW);
    digitalWrite(PIN_GREEN_SWITCH_LED, LOW);
    digitalWrite(PIN_BLUE_SWITCH_LED, LOW);
    digitalWrite(PIN_ENCODER_RED, LOW);
    digitalWrite(PIN_ENCODER_GREEN, LOW);
    digitalWrite(PIN_ENCODER_BLUE, LOW);

    //Set the rest of our pins to INPUT_PULLUP.
    //All of these inputs should switch to ground and be regarded as ACTIVE LOW.
    pinMode(PIN_BLUE_BUTTON, INPUT_PULLUP);
    pinMode(PIN_PINK_BUTTON, INPUT_PULLUP);
    pinMode(PIN_GREEN_BUTTON, INPUT_PULLUP);
    pinMode(PIN_YELLOW_BUTTON, INPUT_PULLUP);

    *portConfigRegister(PIN_RED_SWITCH) = PORT_PCR_MUX(1) | PORT_PCR_PE; //PULLDOWN
    *portConfigRegister(PIN_GREEN_SWITCH) = PORT_PCR_MUX(1) | PORT_PCR_PE; //PULLDOWN
    *portConfigRegister(PIN_BLUE_SWITCH) = PORT_PCR_MUX(1) | PORT_PCR_PE; //PULLDOWN

    pinMode(PIN_SWITCH_0, INPUT_PULLUP);
    pinMode(PIN_SWITCH_1, INPUT_PULLUP);
    pinMode(PIN_SWITCH_2, INPUT_PULLUP);
    pinMode(PIN_SWITCH_3, INPUT_PULLUP);
    pinMode(PIN_ENCODER_BUTTON, INPUT_PULLUP);
    pinMode(PIN_SWITCH_4, INPUT_PULLUP);
    pinMode(PIN_SWITCH_5, INPUT_PULLUP);

    readInputs(gInputs, gInputValues);

    for ( int index = 0; index < gNumPlugins; ++index )
    {
        gPlugins[index]->start();
    }
}

// The loop function is called in an endless loop
void loop()
{
    tone(PIN_BUZZER, 660, 100);
    delay(150);
    tone(PIN_BUZZER, 660, 100);
    delay(300);
    tone(PIN_BUZZER, 660, 100);
    delay(300);
    tone(PIN_BUZZER, 510, 100);
    delay(150);
    tone(PIN_BUZZER, 660, 100);
    delay(300);
    tone(PIN_BUZZER, 770, 100);
    delay(550);
    tone(PIN_BUZZER, 380, 100);
    delay(100);
    noTone(PIN_BUZZER);

//
//    analogWrite(PIN_ENCODER_RED, 100);
//    analogWrite(PIN_ENCODER_GREEN, 0);
//    analogWrite(PIN_ENCODER_BLUE, 0);
//
//    digitalWrite(PIN_RED_SWITCH_LED, true);
//    digitalWrite(PIN_GREEN_SWITCH_LED, true);
//    digitalWrite(PIN_BLUE_SWITCH_LED, true);

//    while (1)
//    {
//        for ( int hue = 0; hue < 255; ++hue )
//        {
//            memset(gLeds, 0,  NUM_LEDS * sizeof(struct CRGB));
//            for(int iLed = 0; iLed < NUM_LEDS; iLed++)
//            {
//
//                int hueOffset = iLed * (128 / NUM_LEDS);
//
//                int ledHue = (hue + hueOffset) % 255;
//
//                gLeds[iLed].setHSV(ledHue, 255, 255);
//            }
//
//            // and now, show your led array!
//            LEDS.show();
//
//            analogWrite(PIN_ENCODER_RED, gLeds[0].red);
//            analogWrite(PIN_ENCODER_GREEN, gLeds[0].green);
//            analogWrite(PIN_ENCODER_BLUE, gLeds[0].blue);
//
//            delay(50);
//        }
//    }


    while (1)
    {
        bool redSwitchLED(false);
        bool greenSwitchLED(false);
        bool blueSwitchLED(false);
        int buzzerFrequency(-1);
        CRGB encoderLED; //This should really be pre-allocated externally and not allocated on the stack every time
        memset((void*)&encoderLED, 0, sizeof(encoderLED)); //This has to happen every loop
        memset((void*)&gLeds, 0, sizeof(gLeds)); //This has to happen every loop

        readInputs(gInputs, gInputValues);

        //Loop through all plugins and allow them to update their internal states for output.
        for ( int index = 0; index < gNumPlugins; ++index )
        {
            gPlugins[index]->step();
        }

        //Loop through all plugins and determine our outputs
        for ( int index = 0; index < gNumPlugins; ++index )
        {
            AbstractInteractionMode::PluginOptions options;
            gPlugins[index]->getPluginOptions(options);
            switch ( options.mPluginComposition )
            {
            case AbstractInteractionMode::CompositeAdditive:
                encoderLED += gPlugins[index]->encoderLed();
                for ( int ledIndex = 0; ledIndex < NUM_LEDS; ++ledIndex )
                {
                    gLeds[ledIndex] += gPlugins[index]->ledBuffer()[ledIndex];
                }
                break;
            case AbstractInteractionMode::CompositeSubtractive:
                encoderLED -= gPlugins[index]->encoderLed();
                for ( int ledIndex = 0; ledIndex < NUM_LEDS; ++ledIndex )
                {
                    gLeds[ledIndex] -= gPlugins[index]->ledBuffer()[ledIndex];
                }
                break;
            }

            redSwitchLED |= gPlugins[index]->redSwitchLed();
            greenSwitchLED |= gPlugins[index]->greenSwitchLed();
            blueSwitchLED |= gPlugins[index]->blueSwitchLed();

            int pluginBuzzer = gPlugins[index]->buzzerFrequency();
            if ( pluginBuzzer > buzzerFrequency )
            {
                buzzerFrequency = pluginBuzzer;
            }
        }

        //Actually set our outputs to our composited values
        LEDS.show();

        analogWrite(PIN_ENCODER_RED, encoderLED.red);
        analogWrite(PIN_ENCODER_GREEN, encoderLED.green);
        analogWrite(PIN_ENCODER_BLUE, encoderLED.blue);

        if ( buzzerFrequency >= 0 )
        {
            tone(PIN_BUZZER, buzzerFrequency );
        }
        else
        {
            noTone(PIN_BUZZER);
        }

        delay(10);
    }
}
