// Do not remove the include below
#include "ButtonBox.h"
#include "PinDefinitions.h"

#include <Encoder.h>
#include <FastSPI_LED2.h>
#include <LowPower_Teensy3.h>

#include "usb_serial.h"
#include "Inputs.h"
#include "PinDefinitions.h"
#include "AbstractInteractionMode.h"

#include "ArcadeButtonActions.h"
#include "RgbEncoderActions.h"
#include "ColorSwitchActions.h"

bool gPluginOverrideEncoder = false;

Inputs gInputs;
InputValues gInputValues;

CRGB gLeds[NUM_LEDS];

ArcadeButtonActions pArcadeButtonTestMode;
RgbEncoderActions pRgbEncoderActions;
ColorSwitchActions pColorSwitchActions;

AbstractInteractionMode * gPlugins[] = { &pArcadeButtonTestMode, &pRgbEncoderActions, &pColorSwitchActions };
const int gNumPlugins = sizeof(gPlugins) / sizeof(AbstractInteractionMode*);

TEENSY3_LP gLowPower = TEENSY3_LP();

int mLastBuzzerFrequency;

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
    int inactivityCount = 0;
    InputValues lastInputValues;
    memset((void*)&lastInputValues, 0, sizeof(lastInputValues));

    tone(PIN_BUZZER, 660, 100);
    delay(150);
//    tone(PIN_BUZZER, 660, 100);
//    delay(300);
//    tone(PIN_BUZZER, 660, 100);
//    delay(300);
//    tone(PIN_BUZZER, 510, 100);
//    delay(150);
//    tone(PIN_BUZZER, 660, 100);
//    delay(300);
//    tone(PIN_BUZZER, 770, 100);
//    delay(550);
//    tone(PIN_BUZZER, 380, 100);
//    delay(100);
    noTone(PIN_BUZZER);
    mLastBuzzerFrequency = 0;

    while (1)
    {
        bool redSwitchLED(false);
        bool greenSwitchLED(false);
        bool blueSwitchLED(false);
        int buzzerFrequency(0);
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

        digitalWrite(PIN_RED_SWITCH_LED, redSwitchLED);
        digitalWrite(PIN_GREEN_SWITCH_LED, greenSwitchLED);
        digitalWrite(PIN_BLUE_SWITCH_LED, blueSwitchLED);

        if ( buzzerFrequency > 0 )
        {
            if ( buzzerFrequency != mLastBuzzerFrequency )
            {
                tone(PIN_BUZZER, buzzerFrequency );
                mLastBuzzerFrequency = buzzerFrequency;
            }
        }
        else
        {
            noTone(PIN_BUZZER);
            mLastBuzzerFrequency = 0;
        }

        if ( lastInputValues != gInputValues )
        {
            inactivityCount = 0;
            lastInputValues = gInputValues;
        }
        else
        {
            inactivityCount++;
        }

        if ( inactivityCount > NUM_INACTIVE_CYCLES_SLEEP )
        {
            //Outputs remain what they are set to in Deep Sleep. Make sure our outputs are all set to off.
            analogWrite(PIN_ENCODER_RED, 0);
            analogWrite(PIN_ENCODER_GREEN, 0);
            analogWrite(PIN_ENCODER_BLUE, 0);

            digitalWrite(PIN_RED_SWITCH_LED, LOW);
            digitalWrite(PIN_GREEN_SWITCH_LED, LOW);
            digitalWrite(PIN_BLUE_SWITCH_LED, LOW);

            noTone(PIN_BUZZER);
            mLastBuzzerFrequency = 0;

            memset((void*)&gLeds, 0, sizeof(gLeds));
            LEDS.show();

            //Delaying here seems to help get the LEDs to turn off
            delay(100);

            LEDS.clear(false);

            *portConfigRegister(PIN_LED_POWER_UP) = PORT_PCR_MUX(1) | PORT_PCR_PE; //PULLDOWN

            gLowPower.DeepSleep(GPIO_WAKE, PIN_2);

            inactivityCount = 0;

            digitalWrite(PIN_LED_POWER_UP, HIGH);
            LEDS.show();
        }

        delay(10);
    }
}
