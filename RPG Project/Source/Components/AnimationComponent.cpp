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
		std::shared_ptr<sf::Texture> textureSheet) :
sprite(sprite)
{
	// initVariables();
	lastAnimation = nullptr;
	priorityAnimation = nullptr;

	// initDefaultValues();
	if (!textureSheet)
	{
		defaultTexture = sprite.getTexture();
	}
	else
	{
		defaultTexture = textureSheet.get();
	}

	defaultTextureRect = sprite.getTextureRect();
}

AnimationComponent::~AnimationComponent()
{
}

void AnimationComponent::addAnimation(
		const std::string key,
		std::shared_ptr<SpriteSequenceAnimation> animation)
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
			animations[key]->play();
			animations[key]->update(dt, modifier);

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
			animations[key]->init();
			lastAnimation = animations[key];
		}

		animations[key]->play();
		animations[key]->update(dt, modifier);
	}
}

void AnimationComponent::stop()
{
	sprite.setTexture(*defaultTexture);
	sprite.setTextureRect(defaultTextureRect);
}

bool AnimationComponent::isDone(std::string key)
{
	return animations[key]->isDone();
}
