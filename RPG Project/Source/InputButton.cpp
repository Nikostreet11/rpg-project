/*
 * InputButton.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: nicop
 */

#include "InputButton.hpp"

InputButton::InputButton()
{
	initVariables();
}

InputButton::InputButton(Type type) :
		InputButton()
{
	this->type = type;
}

InputButton::~InputButton()
{
}

bool InputButton::isPressed()
{
	if (isBeingPressed())
	{
		if (!wasPressed)
		{
			wasPressed = true;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		wasPressed = false;
		return false;
	}
}

bool InputButton::isHold()
{
	if (isBeingPressed())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool InputButton::isReleased()
{
	if (!isBeingPressed())
	{
		if (wasPressed)
		{
			wasPressed = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		wasPressed = true;
		return false;
	}
}

// Getters / Setters

InputButton::Type InputButton::getType() const {
	return type;
}

void InputButton::setType(Type type) {
	this->type = type;
}

short InputButton::getCode() const
{
	return code;
}

void InputButton::setCode(short code)
{
	this->code = code;
}

bool InputButton::isBeingPressed() const
{
	switch (type)
	{
	case keyboardKey:
		return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(code));

	case mouseButton:
		return sf::Mouse::isButtonPressed(sf::Mouse::Button(code));

	default:
		return false;
	}
}

void InputButton::initVariables()
{
	this->type = Type::noType;
	code = -1;
	wasPressed = false;
}
