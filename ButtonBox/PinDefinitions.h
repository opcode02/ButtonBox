/*
 * PinDefinitions.h
 *
 *  Created on: Aug 12, 2013
 *      Author: Ryan
 */

#ifndef PINDEFINITIONS_H_
#define PINDEFINITIONS_H_

    static const int NUM_LEDS = 12;

    static const int PIN_BLUE_BUTTON = 0;
    static const int PIN_PINK_BUTTON = 1;
    static const int PIN_GREEN_BUTTON = 2;
    static const int PIN_YELLOW_BUTTON = 3;

    static const int PIN_RED_SWITCH_LED = 4;
    static const int PIN_GREEN_SWITCH_LED = 5;
    static const int PIN_BLUE_SWITCH_LED = 6;

    static const int PIN_BLUE_SWITCH = 7;
    static const int PIN_RED_SWITCH = 8;
    static const int PIN_GREEN_SWITCH = 9;

    static const int PIN_BUZZER = 10;
    static const int PIN_LED_STRING_DATA = 11;
    static const int PIN_LED_POWER_UP = 12;
    static const int PIN_LED_STRING_CLOCK = 13;

    static const int PIN_SWITCH_0 = 24;//14
    static const int PIN_SWITCH_1 = 25;//15
    static const int PIN_SWITCH_2 = 17;//16
    static const int PIN_SWITCH_3 = 15;//17

    static const int PIN_ENCODER_A = 18;
    static const int PIN_ENCODER_B = 19;

//    From: http://www.pjrc.com/teensy/td_pulse.html
//    Board         PWM Capable Pins
//    Teensy 3.0    3, 4, 5, 6, 9, 10, 20, 21, 22, 23
    static const int PIN_ENCODER_RED = 20;
    static const int PIN_ENCODER_GREEN = 21;
    static const int PIN_ENCODER_BLUE = 22;

    static const int PIN_ENCODER_BUTTON = 23;
    static const int PIN_SWITCH_4 = 16;//24
    static const int PIN_SWITCH_5 = 14;//25


#endif /* PINDEFINITIONS_H_ */
