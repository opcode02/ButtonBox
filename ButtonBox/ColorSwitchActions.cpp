/*
 * ColorSwitchActions.cpp
 *
 *  Created on: Dec 18, 2013
 *      Author: Ryan
 */

#include "ColorSwitchActions.h"

ColorSwitchActions::ColorSwitchActions() : AbstractInteractionMode(),
mLEDIndex(0),
mStepDiv(0)
{
    // TODO Auto-generated constructor stub

}

ColorSwitchActions::~ColorSwitchActions()
{

}



//mLEDIndex = 0
void ColorSwitchActions::step()
{
    mStepDiv++;
    if ( mStepDiv == 10 )
    {
        mStepDiv = 0;

        memset((void*)&mLedBuffer, 0, sizeof(mLedBuffer)); //Turns all of the LEDs off

        if ( gInputValues.mRedSwitch )
        {
            mLedBuffer[mLEDIndex % NUM_LEDS].setRGB(255, 0, 0);
            mLedBuffer[(mLEDIndex - 1) % NUM_LEDS].setRGB(16, 0, 0);
        }

        if ( gInputValues.mGreenSwitch )
        {
            mLedBuffer[(mLEDIndex + 3) % NUM_LEDS].setRGB(0, 255, 0);
            mLedBuffer[(mLEDIndex + 2) % NUM_LEDS].setRGB(0, 16, 0);
        }

        if ( gInputValues.mBlueSwitch )
        {
            mLedBuffer[(mLEDIndex + 6) % NUM_LEDS].setRGB(0, 0, 255);
            mLedBuffer[(mLEDIndex + 5) % NUM_LEDS].setRGB(0, 0, 16);
        }

        if ( gInputValues.mRedSwitch || gInputValues.mGreenSwitch || gInputValues.mBlueSwitch )
        {
            mLEDIndex++;
        }
    }
}
