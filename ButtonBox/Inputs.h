/*
 * Inputs.h
 *
 *  Created on: Aug 13, 2013
 *      Author: Ryan
 */

#ifndef INPUTS_H_
#define INPUTS_H_

#include <Bounce.h>
#include <Encoder.h>

#include "PinDefinitions.h"

struct InputValues
{
    bool mBlueButton;
    bool mPinkButton;
    bool mGreenButton;
    bool mYellowButton;

    bool mSwitch0;
    bool mSwitch1;
    bool mSwitch2;
    bool mSwitch3;
    bool mSwitch4;
    bool mSwitch5;

    bool mEncoderButton;

    bool mRedSwitch;
    bool mBlueSwitch;
    bool mGreenSwitch;

    int mEncoderPosition;
};

struct Inputs
{
    Bounce mBlueButton;
    Bounce mPinkButton;
    Bounce mGreenButton;
    Bounce mYellowButton;

    Bounce mSwitch0;
    Bounce mSwitch1;
    Bounce mSwitch2;
    Bounce mSwitch3;
    Bounce mSwitch4;
    Bounce mSwitch5;

    Bounce mEncoderButton;

    Bounce mRedSwitch;
    Bounce mBlueSwitch;
    Bounce mGreenSwitch;

    Encoder mEncoder;

    Inputs() :
        mBlueButton(PIN_BLUE_BUTTON, 10),
        mPinkButton(PIN_PINK_BUTTON, 10),
        mGreenButton(PIN_GREEN_BUTTON, 10),
        mYellowButton(PIN_YELLOW_BUTTON, 10),
        mSwitch0(PIN_SWITCH_0, 10),
        mSwitch1(PIN_SWITCH_1, 10),
        mSwitch2(PIN_SWITCH_2, 10),
        mSwitch3(PIN_SWITCH_3, 10),
        mSwitch4(PIN_SWITCH_4, 10),
        mSwitch5(PIN_SWITCH_5, 10),
        mEncoderButton(PIN_ENCODER_BUTTON, 10),
        mRedSwitch(PIN_RED_SWITCH, 10),
        mBlueSwitch(PIN_BLUE_SWITCH, 10),
        mGreenSwitch(PIN_GREEN_SWITCH, 10),
        mEncoder(PIN_ENCODER_A,PIN_ENCODER_B)
    {

    }

};

static void readInputs(Inputs & inputs, InputValues & inputValues)
{
    inputs.mBlueButton.update();
    inputs.mPinkButton.update();
    inputs.mGreenButton.update();
    inputs.mYellowButton.update();

    inputs.mSwitch0.update();
    inputs.mSwitch1.update();
    inputs.mSwitch2.update();
    inputs.mSwitch3.update();
    inputs.mSwitch4.update();
    inputs.mSwitch5.update();

    inputs.mEncoderButton.update();

    inputs.mRedSwitch.update();
    inputs.mBlueSwitch.update();
    inputs.mGreenSwitch.update();


    inputValues.mBlueButton = !inputs.mBlueButton.read();
    inputValues.mPinkButton = !inputs.mPinkButton.read();
    inputValues.mGreenButton = !inputs.mGreenButton.read();
    inputValues.mYellowButton = !inputs.mYellowButton.read();

    inputValues.mSwitch0 = !inputs.mSwitch0.read();
    inputValues.mSwitch1 = !inputs.mSwitch1.read();
    inputValues.mSwitch2 = !inputs.mSwitch2.read();
    inputValues.mSwitch3 = !inputs.mSwitch3.read();
    inputValues.mSwitch4 = !inputs.mSwitch4.read();
    inputValues.mSwitch5 = !inputs.mSwitch5.read();

    inputValues.mEncoderButton = inputs.mEncoderButton.read();

    inputValues.mRedSwitch = inputs.mRedSwitch.read();
    inputValues.mBlueSwitch = inputs.mBlueSwitch.read();
    inputValues.mGreenSwitch = inputs.mGreenSwitch.read();

    inputValues.mEncoderPosition = inputs.mEncoder.read();
}

#endif /* INPUTS_H_ */
