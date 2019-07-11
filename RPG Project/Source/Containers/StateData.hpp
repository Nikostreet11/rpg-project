/*
 * StateData.hpp
 *
 *  Created on: May 24, 2019
 *      Author: nicop
 */

#ifndef CONTAINERS_STATEDATA_HPP_
#define CONTAINERS_STATEDATA_HPP_

#include "pch.hpp"

// Forward declarations
class GraphicsSettings;
class State;

class StateData {
public:
	explicit StateData();
	virtual ~StateData();

	// Resources
	std::shared_ptr<GraphicsSettings> graphicsSettings;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<std::map<std::string, int>> supportedKeys;
	std::shared_ptr<std::map<std::string, int>> supportedMouseButtons;
	std::shared_ptr<std::stack<std::unique_ptr<State>>> states;

	// Variables
	float gridSize;
};

#endif /* CONTAINERS_STATEDATA_HPP_ */
