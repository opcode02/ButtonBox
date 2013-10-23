/*
 * AbstractInteractionMode.h
 *
 *  Created on: Aug 12, 2013
 *      Author: Ryan
 */

#ifndef ABSTRACTINTERACTIONMODE_H_
#define ABSTRACTINTERACTIONMODE_H_

#include <stdio.h>
#include <FastSPI_LED2.h>
#include "inputs.h"

extern InputValues gInputValues;

class AbstractInteractionMode
{
public:
    enum CompositionMode { CompositeAdditive, CompositeSubtractive };
    struct PluginOptions
    {
        CompositionMode mPluginComposition;

        PluginOptions() : mPluginComposition(CompositeAdditive) {}
    };

public:
    AbstractInteractionMode() :
        mRedSwitchLED(false),
        mGreenSwitchLED(false),
        mBlueSwitchLED(false),
        mBuzzerFrequency(-1)
    {
        memset((void*)&mEncoderLed, 0, sizeof(mEncoderLed));
        memset((void*)&mLedBuffer, 0, sizeof(mLedBuffer));
    }
    virtual ~AbstractInteractionMode() {}

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

    //This buffer should be populated by the plugin for output to the LED string. This is composited w/ all other plugins once after every call to step.
    const CRGB * ledBuffer() const { return mLedBuffer; }

    //This should be populated by the plugin for output to the RGB Encoder LED. This follows the same compositing rule as the rest of the RGB LEDs.
    CRGB encoderLed() const { return mEncoderLed; }

    //This should be populated by the plugin for output. This is logically OR'd with all other plugins.
    bool redSwitchLed() const { return mRedSwitchLED; }
    //This should be populated by the plugin for output. This is logically OR'd with all other plugins.
    bool greenSwitchLed() const { return mGreenSwitchLED; }
    //This should be populated by the plugin for output. This is logically OR'd with all other plugins.
    bool blueSwitchLed() const { return mBlueSwitchLED; }

    //This should be populated by the plugin for output. This is logically OR'd with all other plugins.
    int buzzerFrequency() const { return mBuzzerFrequency; }

protected:
    CRGB mEncoderLed;
    CRGB mLedBuffer[NUM_LEDS];
    bool mRedSwitchLED;
    bool mGreenSwitchLED;
    bool mBlueSwitchLED;

    int mBuzzerFrequency;
};

#endif /* ABSTRACTINTERACTIONMODE_H_ */
