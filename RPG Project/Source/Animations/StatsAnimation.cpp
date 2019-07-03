/*
 * StatsAnimation.cpp
 *
 *  Created on: Jul 3, 2019
 *      Author: nicop
 */

#include "StatsAnimation.hpp"

StatsAnimation::StatsAnimation(
		sf::Sprite& sprite,
		sf::Texture& textureSheet,
		float animationTimer,
		sf::Vector2u offset,
		sf::Vector2u size,
		sf::Vector2u spacing,
		unsigned value,
		StatType statType,
		bool critical) :
	Animation(
			sprite,
			textureSheet,
			animationTimer,
			std::vector<sf::Vector2u>(),
			offset,
			size,
			spacing)
{
	this->statType = statType;
	this->critical = critical;

	std::string stringValue = std::to_string(value);

	unsigned numberOfDigits = stringValue.length();

	digits.clear();
	digits.resize(numberOfDigits);

	for (size_t index = 0; index < digits.size(); index++)
	{
		sf::Sprite& spriteDigit = digits[index];

		spriteDigit.setTexture(textureSheet);

		unsigned digit = static_cast<unsigned>(stringValue[index]);
		spriteDigit.setTextureRect(sf::IntRect(
				offset.x + (size.x + spacing.x) * getIndex(digit).x,
				offset.y + (size.y + spacing.y) * getIndex(digit).y,
				size.x,
				size.y));
	}

	initPosition();
	initScale();
	initColor();
}

StatsAnimation::~StatsAnimation()
{
}

void StatsAnimation::play(const float& dt, float modifier)
{
	done = false;

	// Set a minimum value for the modifier
	if (modifier < 0.5f)
		modifier = 0.5f;

	// Update timer
	timer += dt * modifier;

	if (timer > animationTimer)
	{
		done = true;
		// Reset timer
		reset();
	}

	// Animate
	for (size_t index = 0; index < digits.size(); index++)
	{
		digits[index].move(0, 100 * dt * modifier);

		sf::Color spriteColor = digits[index].getColor();

		unsigned dAlpha = static_cast<unsigned>(10.f * dt * modifier);

		if (dAlpha > spriteColor.a)
		{
			spriteColor.a = 0;
		}
		else
		{
			spriteColor.a -= dAlpha;
		}

		digits[index].setColor(spriteColor);
	}
}

void StatsAnimation::reset()
{
	timer = 0.f;

	initPosition();
	initColor();
}

// Internal
sf::Vector2u StatsAnimation::getIndex(unsigned digit)
{
	sf::Vector2u index;

	switch (digit)
	{
	case 0:
		index = {20, 0};
		break;

	case 1:
		index = {21, 0};
		break;

	case 2:
		index = {22, 0};
		break;

	case 3:
		index = {23, 0};
		break;

	case 4:
		index = {24, 0};
		break;

	case 5:
		index = {25, 0};
		break;

	case 6:
		index = {26, 0};
		break;

	case 7:
		index = {27, 0};
		break;

	case 8:
		index = {28, 0};
		break;

	case 9:
		index = {29, 0};
		break;

	default:
		index = {20, 0};
		break;
	}

	return index;
}

// Initialization
void StatsAnimation::initVariables()
{
	statType = StatType::Health;
	critical = false;
}

void StatsAnimation::initPosition()
{
	for (size_t index = 0; index < digits.size(); index++)
	{
		sf::Sprite& digit = digits[index];

		digit.setPosition(sprite.getPosition());
		digit.move(
				sprite.getScale().x * sprite.getTextureRect().width * 3/4 +
						digit.getScale().x * size.x * index,
				0);
	}
}

void StatsAnimation::initScale()
{
	// TODO: rework
	for (size_t index = 0; index < digits.size(); index++)
	{
		digits[index].setScale(1, 1);
	}
}

void StatsAnimation::initColor()
{
	for (size_t index = 0; index < digits.size(); index++)
	{
		switch (statType)
		{
		case Health:

			if (critical)
			{
				digits[index].setColor(sf::Color::Yellow);
			}
			else
			{
				digits[index].setColor(sf::Color::White);
			}

			break;

		case Mana:

			digits[index].setColor(sf::Color::Blue);

			break;

		case Stamina:

			digits[index].setColor(sf::Color::Green);

			break;
		}
	}
}
