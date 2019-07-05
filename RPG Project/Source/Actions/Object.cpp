/*
 * Object.cpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#include "Object.hpp"

Object::Object()
{
	initVariables();
}

Object::~Object()
{
}

void Object::initVariables()
{
	healthRestore = 0.f;
	manaRestore = 0.f;
	staminaRestore = 0.f;
}

