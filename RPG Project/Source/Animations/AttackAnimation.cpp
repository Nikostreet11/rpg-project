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
			// Animate
			float firstThreshold = 0.3f;
			float secondThreshold = 0.7f;

			if (timer < duration * firstThreshold)
			{
				sprite.move(
						distance.x / (duration * firstThreshold) * dt * modifier,
						distance.y / (duration * firstThreshold) * dt * modifier);
			}
			else if (timer > duration * secondThreshold)
			{
				sprite.setScale(-startingScale.x, startingScale.y);
				sprite.setOrigin(sprite.getGlobalBounds().width / startingScale.x, 0);
				sprite.move(
						-distance.x / (duration * (1 - secondThreshold)) * dt * modifier,
						-distance.y / (duration * (1 - secondThreshold)) * dt * modifier);
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

void AttackAnimation::render(sf::RenderTarget& target)
{
}

void AttackAnimation::init(
		sf::Vector2f targetPosition,
		sf::Vector2f targetSize)
{
	if (targetPosition.x < sprite.getPosition().x)
	{
		distance.x = targetPosition.x + targetSize.x - sprite.getPosition().x;
	}
	else
	{
		distance.x = targetPosition.x - (sprite.getGlobalBounds().left +
				sprite.getGlobalBounds().width);
	}

	distance.x *= 0.7f;

	distance.y = targetPosition.y + targetSize.y -
			(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);

	startingPosition = sprite.getPosition();
	startingScale = sprite.getScale();

	reset();

	delayTimer = 0;
}

void AttackAnimation::reset()
{
	timer = 0.f;

	sprite.setPosition(startingPosition);
	sprite.setScale(startingScale.x, startingScale.y);
	sprite.setOrigin(0, 0);

	done = true;
}
