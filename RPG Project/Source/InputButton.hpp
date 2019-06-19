/*
 * InputButton.hpp
 *
 *  Created on: Jun 6, 2019
 *      Author: nicop
 */

#ifndef INPUTBUTTON_HPP_
#define INPUTBUTTON_HPP_

#include "pch.hpp"

class InputButton
{
public:
	enum Type
	{
		noType,
		keyboardKey,
		mouseButton
		// joystickButton
	};

	// Constructor / Destructor
	InputButton();
	InputButton(Type type);
	virtual ~InputButton();

	bool isPressed();
	bool isHold();
	bool isReleased();

	// Getters / Setters
	Type getType() const;
	void setType(Type type);
	short getCode() const;
	void setCode(short code);

private:
	// Internal
	bool isBeingPressed() const;

	// Initialization
	void initVariables();

	// Variables
	Type type;
	short code;
	bool wasPressed;
};

#endif /* INPUTBUTTON_HPP_ */
