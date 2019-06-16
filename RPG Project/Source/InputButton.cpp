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

InputButton::~InputButton()
{
}

bool InputButton::isPressed()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(code)))
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(code)))
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
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(code)))
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

short InputButton::getCode() const
{
	return code;
}

void InputButton::setCode(short code)
{
	this->code = code;
}

void InputButton::initVariables()
{
	code = -1;
	wasPressed = false;
}
