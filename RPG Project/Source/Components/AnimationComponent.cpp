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
sprite(sprite),
textureSheet(textureSheet)
{
	this->offset = offset;
	this->size = size;
	this->spacing = spacing;

	// initVariables();
	lastAnimation = nullptr;
	priorityAnimation = nullptr;

	// initDefaultValues();
	defaultTexture = *sprite.getTexture();
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
			textureSheet,
			animationTimer,
			indexVector,
			offset,
			size,
			spacing);
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

// Animation

// Constructor / Destructor
AnimationComponent::Animation::Animation(
		sf::Sprite& sprite,
		std::shared_ptr<sf::Texture> textureSheet,
		float animationTimer,
		std::vector<sf::Vector2u> indexVector,
		sf::Vector2u offset,
		sf::Vector2u size,
		sf::Vector2u spacing) :
	sprite(sprite),
	textureSheet(textureSheet),
	indexVector(indexVector),
	currentIndex(0),
	animationTimer(animationTimer),
	timer(0),
	done(true)
{
	this->offset = offset;
	this->size = size;
	this->spacing = spacing;
}

AnimationComponent::Animation::~Animation()
{
}

// Functions
void AnimationComponent::Animation::play(const float& dt, float modifier)
{
	if (textureSheet)
	{
		this->sprite.setTexture(*textureSheet);
	}

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

void AnimationComponent::Animation::reset()
{
	timer = 0.f;
	currentIndex = 0;

	sprite.setTextureRect(sf::IntRect(
			offset.x + (size.x + spacing.x) * indexVector[0].x,
			offset.y + (size.y + spacing.y) * indexVector[0].y,
			size.x,
			size.y));
}

bool AnimationComponent::Animation::isDone() const
{
	return done;
}
