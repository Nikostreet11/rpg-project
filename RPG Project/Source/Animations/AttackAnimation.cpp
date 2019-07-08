/*
 * AttackAnimation.cpp
 *
 *  Created on: Jul 6, 2019
 *      Author: nicop
 */

#include "AttackAnimation.hpp"

AttackAnimation::AttackAnimation(
		float duration,
		sf::Sprite& sprite) :
	Animation(false, false, duration, sprite, nullptr)
{
	initVariables();
}

AttackAnimation::~AttackAnimation()
{
}

void AttackAnimation::update(const float& dt, float modifier)
{
	if (!done)
	{
		if (delayTimer < delay)
		{
			delayTimer += dt;
		}
		else
		{
			// TODO: Animate
			// sprite.move( ... );

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

void AttackAnimation::render(sf::RenderTarget& target)
{
}

void AttackAnimation::init(
		sf::Vector2f targetPosition,
		sf::Vector2f targetSize)
{
	this->targetPosition = targetPosition;
	this->targetSize = targetSize;

	reset();

	delayTimer = 0;
}

void AttackAnimation::reset()
{
	timer = 0.f;

	sprite.setPosition(startingPosition);

	done = true;
}

void AttackAnimation::initVariables()
{
	startingPosition = sprite.getPosition();
}
