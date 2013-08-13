/*
 * AbstractInteractionMode.h
 *
 *  Created on: Aug 12, 2013
 *      Author: Ryan
 */

#ifndef ABSTRACTINTERACTIONMODE_H_
#define ABSTRACTINTERACTIONMODE_H_

#include <FastSPI_LED2.h>
#include <string.h> //bzero

class AbstractInteractionMode
{
public:
    struct PluginOptions
    {
        //Currently empty
    };

    struct PluginRegistrations
    {
        CRGB mLaunchColor;

        PluginRegistrations() { bzero((void*)&mLaunchColor, sizeof(mLaunchColor)); }
    };

public:
    AbstractInteractionMode() {}
    virtual ~AbstractInteractionMode() {}

    //This should setup any plugin specific configuration. This is run when switching to this plugin.
    virtual void start() {};
    //This should stop any plugin-specific configurations and perform cleanup. This is run when switching to another plugin.
    virtual void stop() {};

    //This registers the plugin for a launch color from the main encoder.
    virtual void getPluginRegistration(PluginRegistrations & registration) = 0;

    //This will setup any plugin-specific configuration options
    virtual void getPluginOptions(PluginOptions & options) {};

    //This is run once per main-loop interval. All work should be done in this method.
    virtual void step() = 0;
};

#endif /* ABSTRACTINTERACTIONMODE_H_ */
