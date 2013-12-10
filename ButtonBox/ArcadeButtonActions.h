/*
 * ArcadeButtonActions.h
 *
 *  Created on: Aug 12, 2013
 *      Author: Ryan
 */

#ifndef ARCADEBUTTONACTIONS_H_
#define ARCADEBUTTONACTIONS_H_

#include "AbstractInteractionMode.h"

class ArcadeButtonActions: public AbstractInteractionMode
{
public:
    ArcadeButtonActions();

    const char * getPluginName() { return "ArcadeButtonActions"; }

    //This is run once per main-loop interval. All work should be done in this method.
    void step();
};

#endif /* ARCADEBUTTONACTIONS_H_ */
