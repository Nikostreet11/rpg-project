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
	bool checkIntersect(const sf::FloatRect& rectangle);

	void update();
	void render(std::shared_ptr<sf::RenderTarget> target);

private:
	// Variables
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::Vector2f offset;
};

#endif /* COMPONENTS_HITBOXCOMPONENT_HPP_ */
