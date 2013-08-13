// Do not remove the include below
#include "ButtonBox.h"
#include "ArcadeButtons.h"

ArcadeButtons gArcadeButtons;
bool gPluginOverrideEncoder = false;

//#define PIN_ENCODER_A 1
//#define PIN_ENCODER_B 2
//
//#define NUM_LEDS 12
//CRGB leds[NUM_LEDS];
//
//
//Encoder encoder = Encoder(1,2);


//The setup function is called once at startup of the sketch
void setup()
{

}

// The loop function is called in an endless loop
void loop()
{
    gArcadeButtons.update();

    delay(10);
}
