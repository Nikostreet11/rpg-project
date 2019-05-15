/*
 * HitboxComponent.hpp
 *
 *  Created on: May 3, 2019
 *      Author: nicop
 */

#ifndef COMPONENTS_HITBOXCOMPONENT_HPP_
#define COMPONENTS_HITBOXCOMPONENT_HPP_

// Streams
#include <iostream>

// Time (legacy)
#include <ctime>

// General utilities (legacy)
#include <cstdlib>

// Smart pointers
#include <memory>

// SFML libraries
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
//#include "SFML/Network.hpp"

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
