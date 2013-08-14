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

    bool mMomentaryLeft;
    bool mMomentaryRight;

    bool mRoundSwitch;

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

    Bounce mMomentaryLeft;
    Bounce mMomentaryRight;

    Bounce mRoundSwitch;

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
        mMomentaryLeft(PIN_MOMENTARY_LEFT, 10),
        mMomentaryRight(PIN_MOMENTARY_RIGHT, 10),
        mRoundSwitch(PIN_ROUND_SWITCH, 10),
        mEncoder(PIN_ENCODER_A,PIN_ENCODER_B)
    {

    }

};

#endif /* INPUTS_H_ */
