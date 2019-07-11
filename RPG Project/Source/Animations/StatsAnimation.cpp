/*
 * StatsAnimation.cpp
 *
 *  Created on: Jul 3, 2019
 *      Author: nicop
 */

#include "StatsAnimation.hpp"

StatsAnimation::StatsAnimation(
		float delay,
		float duration,
		sf::Sprite& sprite,
		const sf::Texture* textureSheet,
		sf::Vector2u offset,
		sf::Vector2u size,
		sf::Vector2u spacing) :
	Animation(false, delay, duration, sprite, textureSheet)
{
	this->offset = offset;
	this->size = size;
	this->spacing = spacing;

	initVariables();
}

StatsAnimation::~StatsAnimation()
{
}

void StatsAnimation::update(const float& dt, float modifier)
{
	if (!done)
	{
		if (delayTimer < delay)
		{
			delayTimer += dt;
		}
		else
		{
			// Animate
			for (size_t index = 0; index < digits.size(); index++)
			{
				digits[index].move(0, -40 * dt * timer * modifier);

				sf::Color spriteColor = digits[index].getColor();

				unsigned dAlpha = static_cast<unsigned>(300.f * dt * timer * modifier);

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

			// Set a minimum value for the modifier (optional)
			if (modifier < 0.5f)
			{
				modifier = 0.5f;
			}

			// Update timer
			timer += dt * modifier;

			if (timer > duration)
			{
				stop();
			}
		}
	}
}

void StatsAnimation::render(sf::RenderTarget& target)
{
	if (delayTimer > delay && !done)
	{
		for (auto &digit : digits)
		{
			target.draw(digit);
		}
	}
}

void StatsAnimation::init(int value, Stat stat, bool critical)
{
	this->stat = stat;
	this->critical = critical;

	if (value < 0)
	{
		healing = true;
		value = std::abs(value);
	}
	else
	{
		healing = false;
	}

	std::string stringValue = std::to_string(value);

	unsigned numberOfDigits = stringValue.length();

	digits.clear();
	digits.resize(numberOfDigits);

	for (size_t index = 0; index < digits.size(); index++)
	{
		sf::Sprite& spriteDigit = digits[index];

		spriteDigit.setTexture(*textureSheet);

		char digit = stringValue[index];

		spriteDigit.setTextureRect(sf::IntRect(
				offset.x + (size.x + spacing.x) * getIndex(digit).x,
				offset.y + (size.y + spacing.y) * getIndex(digit).y,
				size.x,
				size.y));
	}

	reset();

	delayTimer = 0.f;
}

void StatsAnimation::reset()
{
	timer = 0.f;

	initScale();
	initPosition();
	initColor();

	done = true;
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
	healing = false;
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

void StatsAnimation::initColor()
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

			if (healing)
			{
				digits[index].setColor(sf::Color(50, 255, 50, 255));
			}

			break;

		case Mana:

			digits[index].setColor(sf::Color::Blue);

			break;

		case Stamina:

			digits[index].setColor(sf::Color(0, 150, 0, 255));

			break;
		}
	}
}
