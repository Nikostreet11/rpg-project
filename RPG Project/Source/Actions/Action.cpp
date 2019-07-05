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
	name = "DEFAULT_ACTION";

	healthCost = 0.f;
	manaCost = 0.f;
	staminaCost = 0.f;
}

const std::string& Action::getName() const {
	return name;
}
