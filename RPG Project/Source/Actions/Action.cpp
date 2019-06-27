/*
 * Action.cpp
 *
 *  Created on: Jun 27, 2019
 *      Author: nicop
 */

#include "Action.hpp"

Action::Action()
{
	initVariables();
}

Action::~Action()
{
}

void Action::initVariables()
{
	manaCost = 0.f;
	staminaCost = 0.f;
}
