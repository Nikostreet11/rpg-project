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
			float firstThreshold = 0.4f;
			float secondThreshold = 0.475f;
			float thirdThreshold = 0.5f;
			float fourthThreshold = 0.525f;
			float fifthThreshold = 0.6f;

			if (timer < duration * firstThreshold)
			{
				sprite.move(
						movementDistance.x / (duration * firstThreshold) * dt * modifier,
						movementDistance.y / (duration * firstThreshold) * dt * modifier);
			}
			else if (timer < duration * secondThreshold)
			{}
			else if (timer < duration * thirdThreshold)
			{
				sprite.move(attackDistance.x / (duration * (thirdThreshold - secondThreshold)) * dt * modifier, 0);
			}
			else if (timer < duration * fourthThreshold)
			{
				sprite.move(-attackDistance.x / (duration * (fourthThreshold - thirdThreshold)) * dt * modifier, 0);
			}
			else if (timer < duration * fifthThreshold)
			{}
			else// if (timer > duration * thirdThreshold)
			{
				sprite.setScale(-startingScale.x, startingScale.y);
				sprite.setOrigin(sprite.getGlobalBounds().width / startingScale.x, 0);
				sprite.move(
						-movementDistance.x / (duration * (1 - fifthThreshold)) * dt * modifier,
						-movementDistance.y / (duration * (1 - fifthThreshold)) * dt * modifier);
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
		movementDistance.x = targetPosition.x + targetSize.x - sprite.getPosition().x;
	}
	else
	{
		movementDistance.x = targetPosition.x - (sprite.getGlobalBounds().left +
				sprite.getGlobalBounds().width);
	}

	movementDistance.y = targetPosition.y + targetSize.y -
			(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);

	attackDistance = {
			std::copysign(1.f, targetPosition.x - sprite.getPosition().x) * sprite.getGlobalBounds().width * 0.25f,
			0};

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
