/*
 * ArcadeButtons.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: Ryan
 */

#include "ArcadeButtons.h"
#include "PinDefinitions.h"

ArcadeButtons::ArcadeButtons() :
mBlueButton(PIN_BLUE_BUTTON, ARCADE_BUTTON_BOUNCE_INTERVAL),
mPinkButton(PIN_PINK_BUTTON, ARCADE_BUTTON_BOUNCE_INTERVAL),
mGreenButton(PIN_GREEN_BUTTON, ARCADE_BUTTON_BOUNCE_INTERVAL),
mYellowButton(PIN_YELLOW_BUTTON, ARCADE_BUTTON_BOUNCE_INTERVAL)
{
}

ArcadeButtons::~ArcadeButtons()
{

}

int ArcadeButtons::read(Buttons button)
{
    return getButton(button).read();
}

void ArcadeButtons::update()
{
    for ( int index = 0; index < ButtonsMax; ++index )
    {
        update(static_cast<Buttons>(index));
    }
}

void ArcadeButtons::update(Buttons button)
{
    getButton(button).update();
}


Bounce & ArcadeButtons::getButton(Buttons button)
{
    switch ( button )
    {
    case Blue:
        return mBlueButton;
    case Pink:
        return mPinkButton;
    case Green:
        return mGreenButton;
    case Yellow:
    default:
        return mYellowButton;
    }
}

