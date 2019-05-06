/*
 * MovementComponent.cpp
 *
 *  Created on: Apr 24, 2019
 *      Author: nicop
 */

#include "MovementComponent.hpp"

// Static functions

// Constructors / Destructors
MovementComponent::MovementComponent(
		sf::Sprite& sprite,
		float maxSpeed,
		float acceleration,
		float deceleration) :
sprite(sprite),
maxSpeed(maxSpeed),
acceleration(acceleration),
deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
}

// Functions
void MovementComponent::move(const sf::Vector2f& direction, const float& dt)
{
	// Acceleration
	speed.x += acceleration * direction.x;
	speed.y += acceleration * direction.y;
}

void MovementComponent::update(const float& dt)
{
	/* Decelerates the sprite and controls the maximum velocity */

	// Positive x check
	if (speed.x > 0)
	{
		// Max speed check
		if (speed.x > maxSpeed)
			speed.x = maxSpeed;

		// Deceleration
		speed.x -= deceleration;
		if (speed.x < 0)
			speed.x = 0;
	}
	// Negative x check
	else
	{
		// Max speed check
		if (speed.x < -maxSpeed)
			speed.x = -maxSpeed;

		// Deceleration
		speed.x += deceleration;
		if (speed.x > 0)
			speed.x = 0;
	}

	// Positive y check
	if (speed.y > 0)
	{
		// Max speed check
		if (speed.y > maxSpeed)
			speed.y = maxSpeed;

		// Deceleration
		speed.y -= deceleration;
		if (speed.y < 0)
			speed.y = 0;
	}
	// Negative y check
	else
	{
		// Max speed check
		if (speed.y < -maxSpeed)
			speed.y = -maxSpeed;

		// Deceleration
		speed.y += deceleration;
		if (speed.y > 0)
			speed.y = 0;
	}

	sprite.move(speed * dt);
}

// Getters / Setters
bool MovementComponent::isState(State state) const
{
	switch (state)
	{
	case IDLE:
		if (speed.x == 0.f && speed.y == 0.f)
			return true;
		break;

	case MOVING:
		if (speed.x != 0.f || speed.y != 0.f)
			return true;
		break;

	case MOVING_LEFT:
		if (speed.x < 0.f && std::abs(speed.x) >= std::abs(speed.y))
			return true;
		break;

	case MOVING_RIGHT:
		if (speed.x > 0.f && std::abs(speed.x) >= std::abs(speed.y))
			return true;
		break;

	case MOVING_UP:
		if (speed.y < 0.f && std::abs(speed.y) > std::abs(speed.x))
			return true;
		break;

	case MOVING_DOWN:
		if (speed.y > 0.f && std::abs(speed.y) > std::abs(speed.x))
			return true;
		break;
	}

	return false;
}

const sf::Vector2f& MovementComponent::getSpeed() const
{
	return speed;
}

float MovementComponent::getMaxSpeed() const
{
	return maxSpeed;
}
// Initialization functions

