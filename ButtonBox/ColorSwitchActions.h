/*
 * ColorSwitchActions.h
 *
 *  Created on: Dec 18, 2013
 *      Author: Ryan
 */

#ifndef COLORSWITCHACTIONS_H_
#define COLORSWITCHACTIONS_H_

#include "AbstractInteractionMode.h"

class ColorSwitchActions: public AbstractInteractionMode
{
public:
    ColorSwitchActions();
    ~ColorSwitchActions();

    const char * getPluginName() { return "ColorSwitchActions"; }

    //This is run once per main-loop interval. All work should be done in this method.
    void step();

private:
    int mLEDIndex;
    int mStepDiv;
};

#endif /* COLORSWITCHACTIONS_H_ */
