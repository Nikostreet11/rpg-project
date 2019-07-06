/*
 * AttackAnimation.cpp
 *
 *  Created on: Jul 6, 2019
 *      Author: nicop
 */

#include "AttackAnimation.hpp"

AttackAnimation::AttackAnimation(
		sf::Sprite& sprite,
		float animationTimer,
		float delay) :
	Animation(
			sprite,
			nullptr,
			animationTimer,
			std::vector<sf::Vector2u>(),
			sf::Vector2u(),
			sf::Vector2u(),
			sf::Vector2u())
{
	this->delay = delay;

	// InitVariables()
	this->target = nullptr;
}

AttackAnimation::~AttackAnimation()
{
}

void AttackAnimation::update(const float& dt, float modifier)
{
	if (!done)
	{
		//done = false;

		// Set a minimum value for the modifier
		if (modifier < 0.5f)
			modifier = 0.5f;

		// Update timer
		if (delayTimer < delay)
		{
			delayTimer += dt * modifier;
		}
		else
		{
			started = true;

			timer += dt * modifier;

			if (timer > animationTimer)
			{
				done = true;
				//playing = false;
				started = false;
				// Reset timer
				reset();
			}

			// Animate
			//sprite.move(0, -40 * dt * timer * modifier);
		}
	}
}

void AttackAnimation::render(sf::RenderTarget& target)
{
}

void AttackAnimation::play(std::shared_ptr<Character> target)
{
	this->target = target;

	startingPosition = target->getPosition();

	timer = 0;
	delayTimer = 0;

	done = false;
	started = false;
}

void AttackAnimation::reset()
{
	timer = 0.f;
}
