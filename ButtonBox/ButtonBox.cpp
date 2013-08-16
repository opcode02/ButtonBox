// Do not remove the include below
#include "ButtonBox.h"
#include "PinDefinitions.h"

#include <Encoder.h>

#include "Inputs.h"
#include "PinDefinitions.h"

bool gPluginOverrideEncoder = false;

Inputs gInputs;
InputValues gInputValues;

//#define PIN_ENCODER_A 1
//#define PIN_ENCODER_B 2
//
//#define NUM_LEDS 12
//CRGB leds[NUM_LEDS];
//
//
Encoder gEncoder = Encoder(PIN_ENCODER_A,PIN_ENCODER_B);

//The setup function is called once at startup of the sketch
void setup()
{
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
    pinMode(PIN_ENCODER_A, INPUT_PULLUP);
    pinMode(PIN_ENCODER_B, INPUT_PULLUP);
}

// The loop function is called in an endless loop
void loop()
{
    int encoderHue = gInputs.mEncoder.read() % 255;




    delay(10);
}
