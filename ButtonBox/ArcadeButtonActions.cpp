/*
 * ArcadeButtonActions.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: Ryan
 */


#include "ArcadeButtonActions.h"

ArcadeButtonActions::ArcadeButtonActions() : AbstractInteractionMode()
{
}

//This is run once per main-loop interval. All work should be done in this method.
void ArcadeButtonActions::step()
{
    memset((void*)&mLedBuffer, 0, sizeof(mLedBuffer));
    mRedSwitchLED = false;
    mGreenSwitchLED = false;
    mBlueSwitchLED = false;

    if ( gInputValues.mBlueButton )
    {
        mLedBuffer[3].blue = 255;
        mLedBuffer[4].blue = 255;
        mLedBuffer[5].blue = 255;

        mBlueSwitchLED = true;
    }

    if ( gInputValues.mGreenButton )
    {
        mLedBuffer[6].green = 255;
        mLedBuffer[7].green = 255;
        mLedBuffer[8].green = 255;

        mGreenSwitchLED = true;
    }

    if ( gInputValues.mPinkButton )
    {
        mLedBuffer[0].setRGB(255, 50, 50);
        mLedBuffer[1].setRGB(255, 50, 50);
        mLedBuffer[2].setRGB(255, 50, 50);

        mRedSwitchLED = true;
    }

    if ( gInputValues.mYellowButton )
    {
        mLedBuffer[9].setRGB(255, 255, 0);
        mLedBuffer[10].setRGB(255, 255, 0);
        mLedBuffer[11].setRGB(255, 255, 0);
    }

    if ( gInputValues.mSwitch0 )
    {
        mLedBuffer[0].setRGB(255, 255, 255);
    }
    if ( gInputValues.mSwitch1 )
    {
        mLedBuffer[1].setRGB(255, 255, 255);
    }
    if ( gInputValues.mSwitch2 )
    {
        mLedBuffer[2].setRGB(255, 255, 255);
    }
    if ( gInputValues.mSwitch3 )
    {
        mLedBuffer[3].setRGB(255, 255, 255);
    }
    if ( gInputValues.mSwitch4 )
    {
        mLedBuffer[4].setRGB(255, 255, 255);
    }
    if ( gInputValues.mSwitch5 )
    {
        mLedBuffer[5].setRGB(255, 255, 255);
    }

    int switchRed = 0;
    int switchGreen = 0;
    int switchBlue = 0;
    if ( gInputValues.mRedSwitch )
    {
        mLedBuffer[6].red += 255;
    }
    if ( gInputValues.mGreenSwitch )
    {
        mLedBuffer[6].green += 255;
    }
    if ( gInputValues.mBlueSwitch )
    {
        mLedBuffer[6].blue += 255;
    }

}



