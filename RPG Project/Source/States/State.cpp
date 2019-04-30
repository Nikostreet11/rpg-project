/*
 * State.cpp
 *
 *  Created on: Sep 18, 2018
 *      Author: nicop
 */

#include "State.hpp"

// Static functions

// Constructors / Destructors
State::State(
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<std::map<std::string, int>> supportedKeys,
		std::shared_ptr<std::stack<std::unique_ptr<State>>> states) :
window(move(window)),
supportedKeys(move(supportedKeys)),
states(move(states))
{
	ended = false;
}

State::~State()
{
}

// Functions
void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}

// Getters / Setters
const bool& State::isEnded() const
{
	return ended;
}
