/*
 * Player.cpp
 *
 *  Created on: Apr 24, 2019
 *      Author: nicop
 */

#include "Player.hpp"

// Constructors / Destructors
Player::Player(sf::Vector2f position, std::shared_ptr<sf::Texture> textureSheet)
{
	initVariables();

	setTexture(textureSheet);
	setPosition(position);

	createMovement(300.f, 15.f, 5.f);

	createAnimationComponent(textureSheet);
	initAnimations();

	createHitboxComponent(
			sprite,
			sf::Vector2f(20, 10),
			sf::Vector2f(104, 124));
}

Player::~Player()
{
}

// Functions
void Player::update(const float& dt)
{
	movementComponent->update(dt);

	if (movementComponent->isState(MovementComponent::IDLE))
		animationComponent->play("IDLE", dt);

	else if (movementComponent->isState(MovementComponent::MOVING_LEFT))
		animationComponent->play("WALK_LEFT", dt);

	else if (movementComponent->isState(MovementComponent::MOVING_RIGHT))
		animationComponent->play("WALK_RIGHT", dt);

	else if (movementComponent->isState(MovementComponent::MOVING_UP))
		animationComponent->play("WALK_UP", dt);

	else if (movementComponent->isState(MovementComponent::MOVING_DOWN))
		animationComponent->play("WALK_DOWN", dt);

	hitboxComponent->update();
}

// Initialization functions
void Player::initVariables()
{
}

void Player::initAnimations()
{
	std::vector<sf::IntRect> rectVector = {
			sf::IntRect(0, 0, 36, 36),
			sf::IntRect(324, 0, 36, 36),
			sf::IntRect(0, 0, 36, 36),
			sf::IntRect(360, 0, 36, 36)
	};
	animationComponent->addAnimation("IDLE", 0.5f, rectVector);

	rectVector = {
			sf::IntRect(252, 0, 36, 36),
			sf::IntRect(216, 0, 36, 36)
	};
	animationComponent->addAnimation("WALK_LEFT", 0.2f, rectVector);

	rectVector = {
			sf::IntRect(180, 0, 36, 36),
			sf::IntRect(144, 0, 36, 36)
	};
	animationComponent->addAnimation("WALK_RIGHT", 0.2f, rectVector);

	rectVector = {
			sf::IntRect(108, 0, 36, 36),
			sf::IntRect(72, 0, 36, 36)
	};
	animationComponent->addAnimation("WALK_UP", 0.2f, rectVector);

	rectVector = {
			sf::IntRect(36, 0, 36, 36),
			sf::IntRect(0, 0, 36, 36)
	};
	animationComponent->addAnimation("WALK_DOWN", 0.2f, rectVector);

	rectVector = {
			sf::IntRect(648, 0, 36, 36),
			sf::IntRect(684, 0, 36, 36)
	};
	animationComponent->addAnimation("WAVE", 0.5f, rectVector);


}
