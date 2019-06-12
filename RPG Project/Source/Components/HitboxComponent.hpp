/*
 * HitboxComponent.hpp
 *
 *  Created on: May 3, 2019
 *      Author: nicop
 */

#ifndef COMPONENTS_HITBOXCOMPONENT_HPP_
#define COMPONENTS_HITBOXCOMPONENT_HPP_

#include "..\PCH\pch.hpp"

class HitboxComponent
{
public:
	HitboxComponent(
			sf::Sprite& sprite,
			sf::Vector2f offset,
			sf::Vector2f size);
	virtual ~HitboxComponent();

	// Functions
	void update();
	void render(sf::RenderTarget& target);

	bool intersect(const sf::FloatRect& rectangle);

	// Getters / Setters
	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& position);
	const sf::Vector2f& getSize() const;
	void setSize(const sf::Vector2f& size);

private:
	// Resources
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;

	// Variables
	sf::Vector2f offset;
};

#endif /* COMPONENTS_HITBOXCOMPONENT_HPP_ */
