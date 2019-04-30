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

void AnimationComponent::play(const std::string key, const float& dt)
{
	if (animations[key] != lastAnimation)
	{
		animations[key]->reset();
		lastAnimation = animations[key];
	}
	animations[key]->play(dt);
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
	currentRect = 0;
}

AnimationComponent::Animation::~Animation()
{
}

// Functions
void AnimationComponent::Animation::play(const float& dt)
{
	// Update timer
	timer += 1.f * dt;
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
		}

		sprite.setTextureRect(rectVector[currentRect]);
	}
}

void AnimationComponent::Animation::reset()
{
	timer = 0.f;
	currentRect = 0;

	this->sprite.setTexture(*textureSheet, true);
	sprite.setTextureRect(rectVector[0]);
}
