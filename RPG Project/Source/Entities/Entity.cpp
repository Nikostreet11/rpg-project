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
	sprite.setScale(sf::Vector2f(3.5f, 3.5f));
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

void Entity::createAnimationComponent(
		std::shared_ptr<sf::Texture> textureSheet)
{
	animationComponent.reset(new AnimationComponent(
			sprite,
			std::move(textureSheet)));
}

void Entity::createHitboxComponent(
		sf::Sprite& sprite,
		sf::Vector2f offset,
		sf::Vector2f size)
{
	hitboxComponent.reset(new HitboxComponent(sprite, offset, size));
}

// Functions

void Entity::move(float dir_x, float dir_y, const float& dt)
{
	if (movementComponent) {
		movementComponent->move(sf::Vector2f(dir_x, dir_y), dt);
	}
}

void Entity::stop(Axis axis)
{
	if (movementComponent) {
		switch (axis)
		{
		case Axis::X:
			movementComponent->setSpeed(sf::Vector2f(
					0.f,
					movementComponent->getSpeed().y));
			break;

		case Axis::Y:
			movementComponent->setSpeed(sf::Vector2f(
					movementComponent->getSpeed().x,
					0.f));
			break;

		case Axis::NoAxis:
			movementComponent->setSpeed(sf::Vector2f(0.f, 0.f));
			break;
		}
	}
}

// Getters / Setters
const sf::Vector2f& Entity::getPosition() const
{
	if (hitboxComponent)
	{
		return hitboxComponent->getPosition();
	}
	else
	{
		return sprite.getPosition();
	}
}

void Entity::setPosition(const sf::Vector2f& position)
{
	if (hitboxComponent)
	{
		hitboxComponent->setPosition(position);
	}
	else
	{
		sprite.setPosition(position);
	}
}

sf::Vector2f Entity::getNextPosition(const float& dt) const
{
	if (movementComponent)
	{
		if (hitboxComponent)
		{
			return hitboxComponent->getPosition() +
					movementComponent->getSpeed() * dt;
		}
		else
		{
			return sprite.getPosition() + movementComponent->getSpeed() * dt;
		}
	}
	else
	{
		return sprite.getPosition();
	}
}

const sf::Vector2f Entity::getSize() const
{
	if (hitboxComponent)
	{
		return hitboxComponent->getSize();
	}
	else
	{
		return sf::Vector2f(
				sprite.getGlobalBounds().width,
				sprite.getGlobalBounds().height);
	}
}

void Entity::setSize(const sf::Vector2f& size)
{
	if (hitboxComponent)
	{
		hitboxComponent->setSize(size);
	}
	else
	{
		sprite.setScale(
				size.x / sprite.getGlobalBounds().width,
				size.y / sprite.getGlobalBounds().height);
	}
}

// Initialization functions
void Entity::initVariables()
{
	movementComponent = nullptr;
	animationComponent = nullptr;
	hitboxComponent = nullptr;
}
