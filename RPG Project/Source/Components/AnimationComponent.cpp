/*
 * Animation.cpp
 *
 *  Created on: Apr 25, 2019
 *      Author: nicop
 */

#include "AnimationComponent.hpp"

// AnimationComponent

// Constructor / Destructor
AnimationComponent::AnimationComponent(
		sf::Sprite& sprite,
		sf::Vector2u offset,
		sf::Vector2u size,
		sf::Vector2u spacing,
		std::shared_ptr<sf::Texture> textureSheet) :
sprite(sprite)
{
	this->offset = offset;
	this->size = size;
	this->spacing = spacing;

	/*
	if (!textureSheet)
	{
		this->textureSheet = *sprite.getTexture();
	}
	*/

	// initVariables();
	lastAnimation = nullptr;
	priorityAnimation = nullptr;

	// initDefaultValues();
	if (!textureSheet)
	{
		defaultTexture = *sprite.getTexture();
	}
	defaultTextureRect = sprite.getTextureRect();
}

AnimationComponent::~AnimationComponent()
{
}

// Functions
void AnimationComponent::addAnimation(
		const std::string key,
		float animationTimer,
		std::vector<sf::Vector2u>& indexVector)
{
	animations[key] = std::make_shared<Animation>(
			sprite,
			defaultTexture,
			animationTimer,
			indexVector,
			offset,
			size,
			spacing);
}

void AnimationComponent::addAnimation(
		const std::string key,
		std::shared_ptr<Animation> animation)
{
	animations[key] = animation;
}

void AnimationComponent::play(const std::string key, const float& dt,
		const bool priority)
{
	play(key, dt, 1, priority);
}

void AnimationComponent::play(const std::string key, const float& dt,
		const float modifier, const bool priority)
{
	if (priorityAnimation)
	{
		// There is a priority animation playing
		if (priorityAnimation == animations[key])
		{
			// This is the priority animation => Animate
			animations[key]->play(dt, modifier);

			if (animations[key]->isDone())
			{
				// The animation has finished => Unlock the priority
				priorityAnimation = nullptr;
			}
		}
		else
		{
			// This is another animation => Do nothing
		}
	}
	else
	{
		// There isn't a priority animation playing
		if (priority)
		{
			// This is a priority animation => Lock the priority
			priorityAnimation = animations[key];
		}

		if (animations[key] != lastAnimation)
		{
			// This animation is different from the last one
			animations[key]->reset();
			lastAnimation = animations[key];
		}

		animations[key]->play(dt, modifier);
	}
}

void AnimationComponent::stop()
{
	sprite.setTexture(defaultTexture);
	sprite.setTextureRect(defaultTextureRect);
}

bool AnimationComponent::isDone(std::string key)
{
	return animations[key]->isDone();
}
