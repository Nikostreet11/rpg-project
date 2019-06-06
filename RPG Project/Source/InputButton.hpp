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
	// Constructor / Destructor
	InputButton();
	virtual ~InputButton();

	bool isPressed();
	bool isHold();
	bool isReleased();

	// Getters / Setters
	short getCode() const;
	void setCode(short code);

private:
	void initVariables();

	short code;
	bool wasPressed;
};

#endif /* INPUTBUTTON_HPP_ */
