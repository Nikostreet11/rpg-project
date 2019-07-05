/*
 * Animation.cpp
 *
 *  Created on: Jul 3, 2019
 *      Author: nicop
 */

#include "Animation.hpp"

// Constructor / Destructor
Animation::Animation(
		sf::Sprite& sprite,
		const sf::Texture& textureSheet,
		float animationTimer,
		std::vector<sf::Vector2u> indexVector,
		sf::Vector2u offset,
		sf::Vector2u size,
		sf::Vector2u spacing) :
	sprite(sprite),
	textureSheet(textureSheet),
	indexVector(indexVector),
	animationTimer(animationTimer)
{
	this->offset = offset;
	this->size = size;
	this->spacing = spacing;

	initVariables();
}

Animation::~Animation()
{
}

// Functions
void Animation::play(const float& dt, float modifier)
{
	this->sprite.setTexture(textureSheet);

	done = false;

	// Set a minimum value for the modifier
	if (modifier < 0.5f)
		modifier = 0.5f;

	// Update timer
	timer += dt * modifier;
	if (timer > animationTimer)
	{
		// Reset timer
		timer = 0.f;

		// Animate
		if (currentIndex < indexVector.size() - 1)
		{
			currentIndex++;
		}
		// Reset
		else
		{
			currentIndex = 0;
		}

		if (currentIndex == indexVector.size() - 1)
		{
			done = true;
		}

		sprite.setTextureRect(sf::IntRect(
				offset.x + (size.x + spacing.x) * indexVector[currentIndex].x,
				offset.y + (size.y + spacing.y) * indexVector[currentIndex].y,
				size.x,
				size.y));
	}
}

void Animation::reset()
{
	timer = 0.f;
	currentIndex = 0;

	sprite.setTextureRect(sf::IntRect(
			offset.x + (size.x + spacing.x) * indexVector[0].x,
			offset.y + (size.y + spacing.y) * indexVector[0].y,
			size.x,
			size.y));
}

bool Animation::isDone() const
{
	return done;
}

void Animation::initVariables()
{
	started = false;
	done = true;

	timer = 0.f;

	delay = 0.f;
	delayTimer = 0.f;

	currentIndex = 0;
}
