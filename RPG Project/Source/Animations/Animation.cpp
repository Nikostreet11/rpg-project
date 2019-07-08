/*
 * Animation.cpp
 *
 *  Created on: Jul 3, 2019
 *      Author: nicop
 */

#include "Animation.hpp"

// Constructor / Destructor
Animation::Animation(
		bool repeated,
		float delay,
		float duration,
		sf::Sprite& sprite,
		const sf::Texture* textureSheet) :
	sprite(sprite),
	textureSheet(textureSheet)
{
	this->repeated = repeated;

	this->delay = delay;
	this->duration = duration;

	initVariables();
}

Animation::~Animation()
{
}

// Functions
void Animation::play()
{
	done = false;
}

void Animation::pause()
{
	done = true;
}

void Animation::stop()
{
	reset();

	delayTimer = 0.f;

	done = true;
}

// Getters / Setters
bool Animation::isDone() const
{
	return done;
}

void Animation::initVariables()
{
	done = true;

	timer = 0.f;
	delayTimer = 0.f;
}
