/*
 * RgbEncoderActions.h
 *
 *  Created on: Dec 2, 2013
 *      Author: Ryan
 */

#ifndef RGBENCODERACTIONS_H_
#define RGBENCODERACTIONS_H_

#include "AbstractInteractionMode.h"

class RgbEncoderActions: public AbstractInteractionMode
{
public:
    RgbEncoderActions();
    ~RgbEncoderActions();

    const char * getPluginName() { return "RgbEncoderActions"; }

    void step();

private:
    uint8_t  mFadeHue;
    uint8_t  mFadeBrightness;
};

#endif /* RGBENCODERACTIONS_H_ */
