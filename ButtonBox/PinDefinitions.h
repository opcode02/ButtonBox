/*
 * PinDefinitions.h
 *
 *  Created on: Aug 12, 2013
 *      Author: Ryan
 */

#ifndef PINDEFINITIONS_H_
#define PINDEFINITIONS_H_

    static const int PIN_BLUE_BUTTON = 0;
    static const int PIN_PINK_BUTTON = 1;
    static const int PIN_GREEN_BUTTON = 2;
    static const int PIN_YELLOW_BUTTON = 3;

    static const int PIN_RED_SWITCH = 4;
    static const int PIN_GREEN_SWITCH = 5;
    static const int PIN_BLUE_SWITCH = 6;

    static const int PIN_RED_SWITCH_LED = 7;
    static const int PIN_GREEN_SWITCH_LED = 8;
    static const int PIN_BLUE_SWITCH_LED = 9;

    static const int PIN_MOMENTARY_LEFT = 10;
    //11 - LED String Data
    static const int PIN_MOMENTARY_RIGHT = 12;
    //13 - LED String Clock

    //10 - Momentary Left
    static const int PIN_LED_STRING_DATA = 11;
    //12 - Momentary Right
    static const int PIN_LED_STRING_CLOCK = 13;

    static const int PIN_SWITCH_TOP = 14;
    static const int PIN_SWITCH_MID_TOP = 15;
    static const int PIN_SWITCH_MID_BOTTOM = 16;
    static const int PIN_SWITCH_BOTTOM = 17;

    static const int PIN_ROUND_SWITCH = 18;

    static const int PIN_ENCODER_A = 19;
    static const int PIN_ENCODER_B = 20;

//    From: http://www.pjrc.com/teensy/td_pulse.html
//    Board         PWM Capable Pins
//    Teensy 3.0    3, 4, 5, 6, 9, 10, 20, 21, 22, 23
    static const int PIN_ENCODER_RED = 21;
    static const int PIN_ENCODER_GREEN = 22;
    static const int PIN_ENCODER_BLUE = 23;

    //Need more pins for:
    static const int PIN_ROUND_SWITCH_LED = 24;
    static const int PIN_BUZZER = 25;
    static const int PIN_POWER_UP = 26;



#endif /* PINDEFINITIONS_H_ */
