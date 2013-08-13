/*
 * ArcadeButtons.h
 *
 *  Created on: Aug 10, 2013
 *      Author: Ryan
 */

#ifndef ARCADEBUTTONS_H_
#define ARCADEBUTTONS_H_

#include <Bounce.h>

class ArcadeButtons
{
public:
    enum Buttons
    {
        Blue,
        Pink,
        Green,
        Yellow,
        ButtonsMax
    };

public:
	ArcadeButtons();
	~ArcadeButtons();

	void update();
	void update(Buttons button);
	int read(Buttons button);

private:
	static const int ARCADE_BUTTON_BOUNCE_INTERVAL = 5;

private:
    Bounce & getButton(Buttons button);

private:
	Bounce mBlueButton;
    Bounce mPinkButton;
    Bounce mGreenButton;
    Bounce mYellowButton;
};

#endif /* ARCADEBUTTONS_H_ */
