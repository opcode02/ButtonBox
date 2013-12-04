/*
 * RgbEncoderActions.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: Ryan
 */

#include "RgbEncoderActions.h"

RgbEncoderActions::RgbEncoderActions() : AbstractInteractionMode(),
mFadeBrightness(0),
mFadeHue(0)
{
}

RgbEncoderActions::~RgbEncoderActions()
{
}

//This is run once per main-loop interval. All work should be done in this method.
void RgbEncoderActions::step()
{
    int hue = gInputValues.mEncoderPosition % 255;
    mEncoderLed.setHSV(hue, 255, 255);

    if (gInputValues.mEncoderButton )
    {
        mFadeBrightness = 255;
        mFadeHue = hue;
    }

    if ( mFadeBrightness > 12 )
    {
        for ( int i = 0; i < NUM_LEDS; ++i )
        {
            mLedBuffer[i].setHSV(hue, 255, mFadeBrightness);
        }
        mFadeBrightness -= 12;
    }
    else
    {
        memset((void*)&mLedBuffer, 0, sizeof(mLedBuffer));
    }
}

