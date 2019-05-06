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
		std::shared_ptr<sf::Texture> textureSheet
		) :
sprite(sprite),
textureSheet(textureSheet)
{
	lastAnimation = nullptr;
	priorityAnimation = nullptr;
}

AnimationComponent::~AnimationComponent()
{
}

// Functions
void AnimationComponent::addAnimation(
		const std::string key,
		float animationTimer,
		/*sf::Vector2i startFrame,
		sf::Vector2i frames,
		sf::Vector2i size*/
		std::vector<sf::IntRect>& rectVector
		)
{
	animations[key] = std::make_shared<Animation>(
			sprite,
			textureSheet,
			animationTimer,
			rectVector
			);
}

void AnimationComponent::play(const std::string key, const float& dt,
		const bool priority)
{
	if (priorityAnimation)
	{// There is a priority animation playing
		if (priorityAnimation == animations[key])
		{// This is the priority animation => Animate
			animations[key]->play(dt);

			if (animations[key]->isDone())
			{// The animation has finished => Unlock the priority
				priorityAnimation = nullptr;
			}
		}
		else
		{// This is another animation => Do nothing
		}
	}
	else
	{// There isn't a priority animation playing
		if (priority)
		{// This is a priority animation => Lock the priority
			priorityAnimation = animations[key];
		}

		if (animations[key] != lastAnimation)
		{// This animation is different from the last one
			animations[key]->reset();
			lastAnimation = animations[key];
		}
		animations[key]->play(dt);
	}
}

void AnimationComponent::play(const std::string key, const float& dt,
		const float modifier, const bool priority)
{
	if (priorityAnimation)
	{// There is a priority animation playing
		if (priorityAnimation == animations[key])
		{// This is the priority animation => Animate
			animations[key]->play(dt, modifier);

			if (animations[key]->isDone())
			{// The animation has finished => Unlock the priority
				priorityAnimation = nullptr;
			}
		}
		else
		{// This is another animation => Do nothing
		}
	}
	else
	{// There isn't a priority animation playing
		if (priority)
		{// This is a priority animation => Lock the priority
			priorityAnimation = animations[key];
		}

		if (animations[key] != lastAnimation)
		{// This animation is different from the last one
			animations[key]->reset();
			lastAnimation = animations[key];
		}
		animations[key]->play(dt, modifier);
	}
}

void AnimationComponent::playPriorityAnimation(const float& dt)
{
	if (priorityAnimation)
	{
		priorityAnimation->play(dt);

		if (priorityAnimation->isDone())
		{// The animation has finished => Unlock the priority
			priorityAnimation = nullptr;
		}
	}
}

// Animation

// Constructor / Destructor
AnimationComponent::Animation::Animation(
		sf::Sprite& sprite,
		std::shared_ptr<sf::Texture> textureSheet,
		float animationTimer,
		/*sf::Vector2i startFrame,
		sf::Vector2i frames,
		sf::Vector2i size*/
		const std::vector<sf::IntRect>& rectVector
		) :
sprite(sprite),
textureSheet(textureSheet),
animationTimer(animationTimer),
rectVector(rectVector)
//size(size)
{
	timer = 0;
	done = false;
	currentRect = 0;

	this->sprite.setTexture(*textureSheet, true);
}

AnimationComponent::Animation::~Animation()
{
}

// Functions
void AnimationComponent::Animation::play(const float& dt)
{
	done = false;

	// Update timer
	timer += dt;
	if (timer > animationTimer)
	{
		// Reset timer
		timer = 0.f;

		// Animate
		if (currentRect < rectVector.size() - 1)
		{
			currentRect++;
		}
		// Reset
		else
		{
			currentRect = 0;
			done = true;
		}

		sprite.setTextureRect(rectVector[currentRect]);
	}
}

void AnimationComponent::Animation::play(const float& dt, float modifier)
{
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
		if (currentRect < rectVector.size() - 1)
		{
			currentRect++;
		}
		// Reset
		else
		{
			currentRect = 0;
			done = true;
		}

		sprite.setTextureRect(rectVector[currentRect]);
	}
}

void AnimationComponent::Animation::reset()
{
	timer = 0.f;
	currentRect = 0;

	sprite.setTextureRect(rectVector[0]);
}

bool AnimationComponent::Animation::isDone() const
{
	return done;
}
