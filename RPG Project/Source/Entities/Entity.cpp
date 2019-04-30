/*
 * Entity.cpp
 *
 *  Created on: Apr 15, 2019
 *      Author: nicop
 */

#include "Entity.hpp"

// Static functions

// Constructors / Destructors
Entity::Entity()
{
	initVariables();
}

Entity::~Entity()
{
}

// Component functions
void Entity::setTexture(std::shared_ptr<sf::Texture> texture)
{
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 36, 36));
	sprite.setScale(sf::Vector2f(4, 4));
}

void Entity::createMovement(
		float maxSpeed,
		float acceleration,
		float deceleration)
{
	movementComponent.reset(new MovementComponent(
			sprite,
			maxSpeed,
			acceleration,
			deceleration));
}

// Functions
void Entity::setPosition(const sf::Vector2f& position)
{
	sprite.setPosition(position);
}

void Entity::move(float dir_x, float dir_y, const float& dt)
{
	if (movementComponent) {
		movementComponent->move(sf::Vector2f(dir_x, dir_y), dt);
	}
}

void Entity::update(const float& dt)
{
	if (movementComponent) {
		movementComponent->update(dt);
	}
}

void Entity::render(std::shared_ptr<sf::RenderTarget> target)
{
	target->draw(sprite);
}

// Initialization functions
void Entity::initVariables()
{
	movementComponent = nullptr;
	animationComponent = nullptr;
}

void Entity::createAnimationComponent(
		std::shared_ptr<sf::Texture> textureSheet)
{
	animationComponent.reset(new AnimationComponent(
			sprite,
			std::move(textureSheet)));
}
