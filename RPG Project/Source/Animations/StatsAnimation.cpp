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
		sf::Vector2u spacing) :
	Animation(
			sprite,
			textureSheet,
			animationTimer,
			std::vector<sf::Vector2u>(),
			offset,
			size,
			spacing)
{
	initVariables();
}

StatsAnimation::~StatsAnimation()
{
}

void StatsAnimation::update(const float& dt, float modifier)
{
	if (playing)
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
			playing = false;
			// Reset timer
			reset();
		}

		// Animate
		for (size_t index = 0; index < digits.size(); index++)
		{
			digits[index].move(0, -25 * dt * modifier);

			sf::Color spriteColor = digits[index].getColor();

			unsigned dAlpha = static_cast<unsigned>(200.f * dt * modifier);

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
}

void StatsAnimation::render(sf::RenderTarget& target)
{
	if (playing)
	{
		for (auto &digit : digits)
		{
			target.draw(digit);
		}
	}
}

void StatsAnimation::play(unsigned value, Stat stat, bool critical)
{
	this->stat = stat;
	this->critical = critical;

	std::cout << "value: " << value << std::endl;

	std::string stringValue = std::to_string(value);

	std::cout << "stringValue: " << stringValue << std::endl;

	unsigned numberOfDigits = stringValue.length();

	std::cout << "numberOfDigits: " << numberOfDigits << std::endl;

	digits.clear();
	digits.resize(numberOfDigits);

	for (size_t index = 0; index < digits.size(); index++)
	{
		sf::Sprite& spriteDigit = digits[index];

		spriteDigit.setTexture(textureSheet);

		char digit = stringValue[index];
		std::cout << "Digit " << index << ": " << digit << std::endl;
		spriteDigit.setTextureRect(sf::IntRect(
				offset.x + (size.x + spacing.x) * getIndex(digit).x,
				offset.y + (size.y + spacing.y) * getIndex(digit).y,
				size.x,
				size.y));
	}

	timer = 0;

	initScale();
	initPosition();
	initColor(stat, critical);

	playing = true;
}

void StatsAnimation::reset()
{
	timer = 0.f;

	initPosition();
	initColor(stat, critical);
}

// Internal
sf::Vector2u StatsAnimation::getIndex(char digit)
{
	sf::Vector2u index;

	switch (digit)
	{
	case '0':
		index = {20, 0};
		break;

	case '1':
		index = {21, 0};
		break;

	case '2':
		index = {22, 0};
		break;

	case '3':
		index = {23, 0};
		break;

	case '4':
		index = {24, 0};
		break;

	case '5':
		index = {25, 0};
		break;

	case '6':
		index = {26, 0};
		break;

	case '7':
		index = {27, 0};
		break;

	case '8':
		index = {28, 0};
		break;

	case '9':
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
	stat = Health;
	critical = false;

	playing = false;
}

void StatsAnimation::initScale()
{
	// TODO: rework
	for (size_t index = 0; index < digits.size(); index++)
	{
		digits[index].setScale(3.f, 3.f);
	}
}

void StatsAnimation::initPosition()
{
	for (size_t index = 0; index < digits.size(); index++)
	{
		sf::Sprite& digit = digits[index];

		digit.setPosition(sprite.getPosition());
		digit.move(
				sprite.getScale().x * sprite.getTextureRect().width * 0.5f +
						digit.getScale().x * size.x * index * 0.7f,
				0);
	}
}

void StatsAnimation::initColor(Stat stat, bool critical)
{
	for (size_t index = 0; index < digits.size(); index++)
	{
		switch (stat)
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
