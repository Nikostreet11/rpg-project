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
states(move(states)),
supportedKeys(move(supportedKeys))
{
	ended = false;
	paused = false;
}

State::~State()
{
}

void State::pauseState()
{
	paused = true;
}

void State::unpauseState()
{
	paused = false;
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
