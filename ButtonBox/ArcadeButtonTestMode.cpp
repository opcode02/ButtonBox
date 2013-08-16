/*
 * ArcadeButtonTestMode.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: Ryan
 */

#include "ArcadeButtonTestMode.h"

ArcadeButtonTestMode::ArcadeButtonTestMode()
{
}

ArcadeButtonTestMode::~ArcadeButtonTestMode()
{
}

//This registers the plugin for a launch color from the main encoder.
void getPluginRegistration(AbstractInteractionMode::PluginRegistrations & registration)
{
    registration.mLaunchColor = CRGB(128,0,0);
}

//This is run once per main-loop interval. All work should be done in this method.
void step()
{

}



