/*
 * MovementComponent.hpp
 *
 *  Created on: Apr 24, 2019
 *      Author: nicop
 */

#ifndef COMPONENTS_MOVEMENTCOMPONENT_HPP_
#define COMPONENTS_MOVEMENTCOMPONENT_HPP_

// Streams
#include <iostream>
#include <fstream>
#include <sstream>

// Time (legacy)
#include <ctime>

// General utilities (legacy)
#include <cstdlib>

// Data structures
#include <vector>
#include <stack>
#include <map>

// Smart pointers
#include <memory>

// SFML libraries
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
//#include "SFML/Network.hpp"

class MovementComponent {
public:
	// Enumerators
	enum State {
		IDLE = 0,
		MOVING,
		MOVING_LEFT,
		MOVING_RIGHT,
		MOVING_UP,
		MOVING_DOWN
	};

	// Static functions

	// Constructors / Destructors
	explicit MovementComponent(
			sf::Sprite& sprite,
			float maxSpeed,
			float acceleraton,
			float deceleration);
	virtual ~MovementComponent();

	// Functions
	void move(const sf::Vector2f& direction, const float& dt);
	void update(const float& dt);

	// Getters / Setters
	const sf::Vector2f& getSpeed() const;
	bool isState(State state) const;
	float getMaxSpeed() const;

private:
	// Initialization functions

	// Variables
	sf::Sprite& sprite;

	float maxSpeed;
	float acceleration;
	float deceleration;

	sf::Vector2f speed;
};

#endif /* COMPONENTS_MOVEMENTCOMPONENT_HPP_ */
