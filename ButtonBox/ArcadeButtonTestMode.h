/*
 * ArcadeButtonTestMode.h
 *
 *  Created on: Aug 12, 2013
 *      Author: Ryan
 */

#ifndef ARCADEBUTTONTESTMODE_H_
#define ARCADEBUTTONTESTMODE_H_

#include "AbstractInteractionMode.h"

class ArcadeButtonTestMode: public AbstractInteractionMode
{
public:
    ArcadeButtonTestMode();
    ~ArcadeButtonTestMode();

    //This registers the plugin for a launch color from the main encoder.
    void getPluginRegistration(AbstractInteractionMode::PluginRegistrations & registration);

    //This is run once per main-loop interval. All work should be done in this method.
    void step();
};

#endif /* ARCADEBUTTONTESTMODE_H_ */
