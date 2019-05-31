/*
 * State.cpp
 *
 *  Created on: Sep 18, 2018
 *      Author: nicop
 */

#include "State.hpp"

// Static functions

// Constructors / Destructors
State::State(StateData& stateData) :
		stateData(stateData),
		graphicsSettings(stateData.graphicsSettings),
		window(stateData.window),
		supportedKeys(stateData.supportedKeys),
		states(stateData.states),
		gridSize(stateData.gridSize)
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

