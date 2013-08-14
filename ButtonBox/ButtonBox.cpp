// Do not remove the include below
#include "ButtonBox.h"
#include "PinDefinitions.h"

#include <Encoder.h>

#include "Inputs.h"

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

}

// The loop function is called in an endless loop
void loop()
{
    int encoderHue = gInputs.mEncoder.read() % 255;




    delay(10);
}
