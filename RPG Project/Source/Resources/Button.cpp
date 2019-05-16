/*
 * Button.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: nicop
 */

#include "Button.hpp"

namespace gui {

// Constructors / Destructors
Button::Button(
		sf::Vector2f position,
		sf::Vector2f size,
		std::shared_ptr<sf::Font> font,
		std::string text,
		unsigned characterSize,
		sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) :
font(move(font))
{
	state = states::Idle;
	wasPressed = false;

	shape.setPosition(position);
	shape.setSize(size);

	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(characterSize);
	this->text.setPosition(
			shape.getPosition().x + shape.getGlobalBounds().width / 2.f -
				this->text.getGlobalBounds().width / 2.f,
			shape.getPosition().y + shape.getGlobalBounds().height / 2.f -
				this->text.getCharacterSize() / 2.f);

	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	shape.setFillColor(idleColor);
}

Button::~Button()
{
}

// Functions
void Button::update(const sf::Vector2f& mousePos)
{
	/* Update the booleans for hover and pressed */

	if (shape.getGlobalBounds().contains(mousePos))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (state == states::Hover)
				state = states::Active;
		}
		else
		{
			state = states::Hover;
			wasPressed = false;
		}
	}
	else
	{
		state = states::Idle;
		wasPressed = false;
	}

	switch (state)
	{
	case states::Idle:
		shape.setFillColor(idleColor);
		text.setFillColor(textIdleColor);
		break;

	case states::Hover:
		shape.setFillColor(hoverColor);
		text.setFillColor(textHoverColor);
		break;

	case states::Active:
		shape.setFillColor(activeColor);
		text.setFillColor(textActiveColor);
		break;

	default:
		shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(std::shared_ptr<sf::RenderTarget> target)
{
	target->draw(shape);
	target->draw(text);
}

bool Button::isPressed()
{
	if (state == states::Active && !wasPressed)
	{
		wasPressed = true;
		return true;
	}
	else
	{
		return false;
	}
}

bool Button::isHold() const
{
	if (state == states::Active)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*bool Button::isReleased()
{
	if (state != states::Active && wasPressed)
	{
		wasPressed = false;
		return true;
	}
	else
	{
		return false;
	}
}*/

// Getters / Setters
const std::string Button::getText() const
{
	return text.getString();
}

void Button::setText(const std::string& text)
{
	this->text.setString(text);
}

} /* namespace gui */
