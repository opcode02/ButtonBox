/*
 * ArcadeButtonTestMode.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: Ryan
 */


#include "ArcadeButtonTestMode.h"

ArcadeButtonTestMode::ArcadeButtonTestMode() : AbstractInteractionMode()
{
}

//This is run once per main-loop interval. All work should be done in this method.
void ArcadeButtonTestMode::step()
{
    memset((void*)&mLedBuffer, 0, sizeof(mLedBuffer));

    if ( gInputValues.mBlueButton )
    {
        mLedBuffer[0].blue = 255;
        mLedBuffer[1].blue = 255;
        mLedBuffer[2].blue = 255;
    }

    if ( gInputValues.mGreenButton )
    {
        mLedBuffer[3].green = 255;
        mLedBuffer[4].green = 255;
        mLedBuffer[5].green = 255;
    }

    if ( gInputValues.mPinkButton )
    {
        mLedBuffer[6].setRGB(255, 200, 200);
        mLedBuffer[7].setRGB(255, 200, 200);
        mLedBuffer[8].setRGB(255, 200, 200);
    }

    if ( gInputValues.mYellowButton )
    {
        mLedBuffer[9].setRGB(255, 255, 0);
        mLedBuffer[10].setRGB(255, 255, 0);
        mLedBuffer[11].setRGB(255, 255, 0);
    }
}



