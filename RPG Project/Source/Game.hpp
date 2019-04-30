/*
 * Game.h
 *
 *  Created on: Jul 26, 2018
 *      Author: nicop
 */

#ifndef GAME_HPP_
#define GAME_HPP_

/*#include "GraphicEngine.h"
#include "ServiceLocator.h"
#include "NavigationEntry.h"
#include "State.h"*/

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

	/*void start();

	void changeState(State* newState);*/

private:
	/*void draw();
	void manageInput();*/

	// Initialization functions
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();

	// Variables
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videomodes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock;
	float dt;

	std::shared_ptr<std::stack<std::unique_ptr<State>>> states;
	std::shared_ptr<std::map<std::string, int>> supportedKeys;
	// State* state;
};

#endif /* GAME_HPP_ */
