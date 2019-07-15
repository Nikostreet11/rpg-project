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

	createMovement(450.f, 4000.f, 2000.f);

	createAnimationComponent(textureSheet);
	initAnimations();

	createHitboxComponent(
			sprite,
			{8, 80}, {96, 32});
			//{10, 5}, {90, 110});
}

Player::~Player()
{
}

// Functions
void Player::update(const float& dt)
{
	movementComponent->update(dt);

	updateAnimations(dt);

	hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(sprite);

	hitboxComponent->render(target);
}

void Player::updateAnimations(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) ||
			!animationComponent->isDone("WAVE"))
		animationComponent->play("WAVE", dt, true);

	if (movementComponent->isState(MovementComponent::IDLE))
		animationComponent->play("IDLE", dt);

	if (movementComponent->isState(MovementComponent::MOVING_LEFT))
		animationComponent->play("WALK_LEFT", dt, std::abs(
				movementComponent->getSpeed().x /
				movementComponent->getMaxSpeed()));

	if (movementComponent->isState(MovementComponent::MOVING_RIGHT))
		animationComponent->play("WALK_RIGHT", dt, std::abs(
				movementComponent->getSpeed().x /
				movementComponent->getMaxSpeed()));

	if (movementComponent->isState(MovementComponent::MOVING_UP))
		animationComponent->play("WALK_UP", dt, std::abs(
				movementComponent->getSpeed().y /
				movementComponent->getMaxSpeed()));

	if (movementComponent->isState(MovementComponent::MOVING_DOWN))
		animationComponent->play("WALK_DOWN", dt, std::abs(
				movementComponent->getSpeed().y /
				movementComponent->getMaxSpeed()));
}

// Initialization functions
void Player::initVariables()
{
}

void Player::initAnimations()
{
	std::vector<sf::Vector2u> indexVector = {{0, 0}, {9, 0}, {0, 0}, {10, 0}};
	animationComponent->addAnimation(
			"IDLE",
			std::move(std::make_shared<SpriteSequenceAnimation>(
					true, 0.f, 2.f,
					sprite, nullptr,
					indexVector,
					sf::Vector2u(2, 2),
					sf::Vector2u(32, 32),
					sf::Vector2u(4, 4))));

	indexVector = {{7, 0}, {6, 0}};
	animationComponent->addAnimation(
			"WALK_LEFT",
			std::move(std::make_shared<SpriteSequenceAnimation>(
					true, 0.f, 0.4f,
					sprite, nullptr,
					indexVector,
					sf::Vector2u(2, 2),
					sf::Vector2u(32, 32),
					sf::Vector2u(4, 4))));

	indexVector = {{5, 0}, {4, 0}, {5, 0}, {4, 0}};
	animationComponent->addAnimation(
			"WALK_RIGHT",
			std::move(std::make_shared<SpriteSequenceAnimation>(
					true, 0.f, 0.8f,
					sprite, nullptr,
					indexVector,
					sf::Vector2u(2, 2),
					sf::Vector2u(32, 32),
					sf::Vector2u(4, 4))));

	indexVector = {{3, 0}, {2, 0}};

	animationComponent->addAnimation(
			"WALK_UP",
			std::move(std::make_shared<SpriteSequenceAnimation>(
					true, 0.f, 0.4f,
					sprite, nullptr,
					indexVector,
					sf::Vector2u(2, 2),
					sf::Vector2u(32, 32),
					sf::Vector2u(4, 4))));

	indexVector = {{1, 0}, {0, 0}};
	animationComponent->addAnimation(
			"WALK_DOWN",
			std::move(std::make_shared<SpriteSequenceAnimation>(
					true, 0.f, 0.4f,
					sprite, nullptr,
					indexVector,
					sf::Vector2u(2, 2),
					sf::Vector2u(32, 32),
					sf::Vector2u(4, 4))));

	indexVector = {{18, 0}, {19, 0}, {18, 0}, {19, 0}, {18, 0}};
	animationComponent->addAnimation(
			"WAVE",
			std::move(std::make_shared<SpriteSequenceAnimation>(
					false, 0.f, 1.f,
					sprite, nullptr,
					indexVector,
					sf::Vector2u(2, 2),
					sf::Vector2u(32, 32),
					sf::Vector2u(4, 4))));

	/*
	indexVector = {	// 0 5 2 7 0 5 2 7 11 11 11 11 8 8
			{0, 0}, {5, 0}, {2, 0}, {7, 0},
			{0, 0}, {5, 0}, {2, 0}, {7, 0},
			{11, 0}, {11, 0}, {11, 0}, {11, 0}, {8, 0}, {8, 0}};

	animationComponent->addAnimation("SPIN", 0.2f, indexVector);
	*/
}
