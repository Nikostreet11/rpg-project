/*
 * Entity.hpp
 *
 *  Created on: Apr 15, 2019
 *      Author: nicop
 */

#ifndef ENTITIES_ENTITY_HPP_
#define ENTITIES_ENTITY_HPP_

#include "../Components/AnimationComponent.hpp"
#include "../Components/MovementComponent.hpp"

class Entity
{
public:
	// Static functions

	// Constructors / Destructors
	Entity();
	virtual ~Entity();

	// Component functions
	void setTexture(std::shared_ptr<sf::Texture> texture);
	void createMovement(
			float maxSpeed,
			float acceleration,
			float deceleration);
	void createAnimationComponent(
			std::shared_ptr<sf::Texture> textureSheet);

	// Functions
	virtual void setPosition(const sf::Vector2f& position);
	virtual void move(float dir_x, float dir_y, const float& dt);

	virtual void update(const float& dt);
	virtual void render(std::shared_ptr<sf::RenderTarget> target);

protected:
	// Initialization functions
	void initVariables();

	// Variables
	sf::Sprite sprite;

	std::unique_ptr<MovementComponent> movementComponent;
	std::unique_ptr<AnimationComponent> animationComponent;
};

#endif /* ENTITIES_ENTITY_HPP_ */
