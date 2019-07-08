/*
 * SpriteSequenceAnimation.cpp
 *
 *  Created on: Jul 8, 2019
 *      Author: Nikostreet11
 */

#include "SpriteSequenceAnimation.hpp"

SpriteSequenceAnimation::SpriteSequenceAnimation(
		bool repeated,
		float delay,
		float duration,
		sf::Sprite& sprite,
		const sf::Texture* textureSheet,
		std::vector<sf::Vector2u> indexVector,
		sf::Vector2u offset,
		sf::Vector2u size,
		sf::Vector2u spacing) :
	Animation(repeated, delay, duration, sprite, textureSheet)
{
	this->indexVector = indexVector;

	this->offset = offset;
	this->size = size;
	this->spacing = spacing;

	initVariables();
}

SpriteSequenceAnimation::~SpriteSequenceAnimation()
{
}

// Functions
void SpriteSequenceAnimation::update(const float& dt, float modifier)
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
			sprite.setTextureRect(sf::IntRect(
					offset.x + (size.x + spacing.x) * indexVector[currentIndex].x,
					offset.y + (size.y + spacing.y) * indexVector[currentIndex].y,
					size.x,
					size.y));

			// Set a minimum value for the modifier (optional)
			if (modifier < 0.5f)
			{
				modifier = 0.5f;
			}

			// Update timer
			timer += dt * modifier;

			if (timer > duration / static_cast<float>(indexVector.size()))
			{
				// Reset timer
				timer = 0.f;

				// Animate
				if (currentIndex < indexVector.size() - 1)
				{
					currentIndex++;
				}
				else if (currentIndex == indexVector.size() - 1)
				{
					if (repeated)
					{
						reset();
					}
					else
					{
						stop();
					}
				}
			}
		}
	}
}

void SpriteSequenceAnimation::render(sf::RenderTarget& target)
{
}

void SpriteSequenceAnimation::init()
{
	reset();

	delayTimer = 0.f;
}

void SpriteSequenceAnimation::reset()
{
	timer = 0.f;
	currentIndex = 0;

	if (!textureSheet)
	{
		textureSheet = sprite.getTexture();
	}

	sprite.setTexture(*textureSheet);

	sprite.setTextureRect(sf::IntRect(
			offset.x + (size.x + spacing.x) * indexVector[currentIndex].x,
			offset.y + (size.y + spacing.y) * indexVector[currentIndex].y,
			size.x,
			size.y));
}

// Initialization
void SpriteSequenceAnimation::initVariables()
{
	currentIndex = 0;
}

