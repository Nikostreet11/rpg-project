/*
 * HitboxComponent.hpp
 *
 *  Created on: May 3, 2019
 *      Author: nicop
 */

#ifndef COMPONENTS_HITBOXCOMPONENT_HPP_
#define COMPONENTS_HITBOXCOMPONENT_HPP_

#include "..\PCH\pch.hpp"
/*
// Utilities
#include <utility>
#include <thread>
#include <algorithm>

// Legacy
#include <cstdlib>
#include <ctime>
#include <cmath>

// Data structures
#include <set>
#include <list>
#include <deque>
#include <stack>
#include <vector>
#include <map>

// Smart Pointers
#include <memory>

// Data types
#include <string>

// Stream
#include <iostream>
#include <fstream>
#include <sstream>

// SFML
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
*/

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
