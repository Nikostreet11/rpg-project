/*
 * Game.h
 *
 *  Created on: Jul 26, 2018
 *      Author: nicop
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include "Containers\StateData.hpp"
#include "Containers\GraphicsSettings.hpp"
#include "States/MainMenuState.hpp"

class Game {
public:
	// Static functions

	// Constructors / Destructors
	Game();
	virtual ~Game();

	// Functions
	// --Core
	void run();
	void close();

	// --Update
	void update();
	void updateDt();
	void updateSFMLEvents();

	// --Render
	void render();

private:

	// Initialization functions
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStates();
	void initStateData();

	void start();

	// Resources
	StateData stateData;

	std::shared_ptr<GraphicsSettings> graphicsSettings;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<std::map<std::string, int>> supportedKeys;
	std::shared_ptr<std::stack<std::unique_ptr<State>>> states;

	sf::Event sfEvent;
	sf::Clock dtClock;


	// Variables
	float dt;
	float gridSize;

};

#endif /* GAME_HPP_ */
