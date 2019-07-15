/*
 * Button.cpp
 *
 *  Created on: Apr 22, 2019
 *      Author: nicop
 */

#include "Button.hpp"

namespace gui {

// Constructor / Destructor
Button::Button(
		sf::Vector2f position,
		sf::Vector2f size,
		std::shared_ptr<sf::Font> font,
		std::string text,
		unsigned characterSize,
		sf::Color textIdleColor,
		sf::Color textHoverColor,
		sf::Color textActiveColor,
		sf::Color fillIdleColor,
		sf::Color fillHoverColor,
		sf::Color fillActiveColor,
		sf::Color outlineIdleColor,
		sf::Color outlineHoverColor,
		sf::Color outlineActiveColor) :
font(move(font))
{
	initVariables();

	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(fillIdleColor);
	shape.setOutlineThickness(1.f);
	shape.setOutlineColor(outlineIdleColor);

	this->text.setFont(*this->font);
	this->text.setFillColor(textIdleColor);
	this->text.setCharacterSize(characterSize);
	setText(text);

	this->textIdleColor = textIdleColor;
	this->textHoverColor = textHoverColor;
	this->textActiveColor = textActiveColor;

	this->fillIdleColor = fillIdleColor;
	this->fillHoverColor = fillHoverColor;
	this->fillActiveColor = fillActiveColor;

	// TODO: modify later
	this->outlineIdleColor = outlineIdleColor;
	this->outlineHoverColor = outlineHoverColor;
	this->outlineActiveColor = outlineActiveColor;
}

Button::~Button()
{
}

// Functions
void Button::update(const sf::Vector2i& mousePosWindow)
{
	/* Update the booleans for hover and pressed */

	if (shape.getGlobalBounds().contains(
			static_cast<sf::Vector2f>(mousePosWindow))) // Selection
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Input
		{
			if (state == states::Hover)
			{
				state = states::Active;
				pressEvent = true;
			}
		}
		else
		{
			if (state == states::Active)
			{
				releaseEvent = true;
			}

			state = states::Hover;
		}
	}
	else
	{
		state = states::Idle;
		// pressEvent = false;
		// releaseEvent = false;
	}

	switch (state)
	{
	case states::Idle:
		shape.setFillColor(fillIdleColor);
		shape.setOutlineColor(outlineIdleColor);
		text.setFillColor(textIdleColor);
		break;

	case states::Hover:
		shape.setFillColor(fillHoverColor);
		shape.setOutlineColor(outlineHoverColor);
		text.setFillColor(textHoverColor);
		break;

	case states::Active:
		shape.setFillColor(fillActiveColor);
		shape.setOutlineColor(outlineActiveColor);
		text.setFillColor(textActiveColor);
		break;

	default:
		shape.setFillColor(sf::Color::Red);
		shape.setOutlineColor(sf::Color::Green);
		text.setFillColor(sf::Color::Blue);
		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
}

bool Button::isPressed()
{
	// TODO: verify if the state check is mandatory
	if (state == states::Active && pressEvent)
	{
		pressEvent = false;
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

bool Button::isReleased()
{
	if (state == states::Hover && releaseEvent)
	{
		releaseEvent = false;
		return true;
	}
	else
	{
		return false;
	}
}

// Getters / Setters
const std::string Button::getText() const
{
	return text.getString();
}

void Button::setText(const std::string& text)
{
	this->text.setString(text);

	this->text.setPosition(
			shape.getPosition().x + shape.getGlobalBounds().width / 2.f -
				this->text.getGlobalBounds().width / 2.f,
			shape.getPosition().y + shape.getGlobalBounds().height / 2.f -
				this->text.getCharacterSize() * 1.3f / 2.f);
}

sf::FloatRect Button::getGlobalBounds() const
{
	return shape.getGlobalBounds();
}

void gui::Button::initVariables()
{
	state = states::Idle;
	pressEvent = false;
	releaseEvent = false;
}

} /* namespace gui */
