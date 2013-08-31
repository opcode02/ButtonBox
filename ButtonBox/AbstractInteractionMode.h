/*
 * AbstractInteractionMode.h
 *
 *  Created on: Aug 12, 2013
 *      Author: Ryan
 */

#ifndef ABSTRACTINTERACTIONMODE_H_
#define ABSTRACTINTERACTIONMODE_H_

#include <string.h> //bzero

class AbstractInteractionMode
{
public:
    struct PluginOptions
    {
        //Currently empty
    };

public:
    AbstractInteractionMode() {}

    //This should setup any plugin specific configuration. This is run when switching to this plugin.
    virtual void start() {};
    //This should stop any plugin-specific configurations and perform cleanup. This is run when switching to another plugin.
    virtual void stop() {};

    //This will setup any plugin-specific configuration options
    virtual void getPluginOptions(PluginOptions & options) {};

    //This must return a serial-friendly name for the plugin. This is solely for debugging which mode is running via serial.
    virtual const char * getPluginName() = 0;

    //This is run once per main-loop interval. All work should be done in this method.
    virtual void step() = 0;
};

#endif /* ABSTRACTINTERACTIONMODE_H_ */
