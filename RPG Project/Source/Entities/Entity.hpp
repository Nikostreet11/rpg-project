/*
 * Entity.hpp
 *
 *  Created on: Apr 15, 2019
 *      Author: nicop
 */

#ifndef ENTITIES_ENTITY_HPP_
#define ENTITIES_ENTITY_HPP_

#include "..\Components\AnimationComponent.hpp"
#include "..\Components\MovementComponent.hpp"
#include "..\Components\HitboxComponent.hpp"
#include "..\Map\Axis.hpp"

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
	void createHitboxComponent(
			sf::Sprite& sprite,
			sf::Vector2f offset,
			sf::Vector2f size);

	// Functions
	virtual void move(float dir_x, float dir_y, const float& dt);
	virtual void stop(Axis axis = Axis::NoAxis);
	virtual bool intersects(sf::FloatRect rectangle) const;

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

	// Getters / Setters
	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& position);
	const sf::Vector2f getSize() const;
	void setSize(const sf::Vector2f& size);
	sf::FloatRect getGlobalBounds() const;
	sf::Vector2f getNextPosition(const float& dt) const;
	sf::FloatRect getNextGlobalBounds(const float& dt) const;

protected:
	// Initialization functions
	void initVariables();

	// Variables
	sf::Sprite sprite;

	std::unique_ptr<HitboxComponent> hitboxComponent;
	std::unique_ptr<MovementComponent> movementComponent;
	std::unique_ptr<AnimationComponent> animationComponent;
};

#endif /* ENTITIES_ENTITY_HPP_ */
