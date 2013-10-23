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

    bool mSwitchTop;
    bool mSwitchMidTop;
    bool mSwitchMidBottom;
    bool mSwitchBottom;

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

    Bounce mSwitchTop;
    Bounce mSwitchMidTop;
    Bounce mSwitchMidBottom;
    Bounce mSwitchBottom;

    Bounce mRedSwitch;
    Bounce mBlueSwitch;
    Bounce mGreenSwitch;

    Encoder mEncoder;

    Inputs() :
        mBlueButton(PIN_BLUE_BUTTON, 10),
        mPinkButton(PIN_PINK_BUTTON, 10),
        mGreenButton(PIN_GREEN_BUTTON, 10),
        mYellowButton(PIN_YELLOW_BUTTON, 10),
        mSwitchTop(PIN_SWITCH_TOP, 10),
        mSwitchMidTop(PIN_SWITCH_MID_TOP, 10),
        mSwitchMidBottom(PIN_SWITCH_MID_BOTTOM, 10),
        mSwitchBottom(PIN_SWITCH_BOTTOM, 10),
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

    inputs.mSwitchTop.update();
    inputs.mSwitchMidTop.update();
    inputs.mSwitchMidBottom.update();
    inputs.mSwitchBottom.update();

    inputs.mRedSwitch.update();
    inputs.mBlueSwitch.update();
    inputs.mGreenSwitch.update();


    inputValues.mBlueButton = inputs.mBlueButton.read();
    inputValues.mPinkButton = inputs.mPinkButton.read();
    inputValues.mGreenButton = inputs.mGreenButton.read();
    inputValues.mYellowButton = inputs.mYellowButton.read();

    inputValues.mSwitchTop = inputs.mSwitchTop.read();
    inputValues.mSwitchMidTop = inputs.mSwitchMidTop.read();
    inputValues.mSwitchMidBottom = inputs.mSwitchMidBottom.read();
    inputValues.mSwitchBottom = inputs.mSwitchBottom.read();

    inputValues.mRedSwitch = inputs.mRedSwitch.read();
    inputValues.mBlueSwitch = inputs.mBlueSwitch.read();
    inputValues.mGreenSwitch = inputs.mGreenSwitch.read();

    inputValues.mEncoderPosition = inputs.mEncoder.read();
}

#endif /* INPUTS_H_ */
