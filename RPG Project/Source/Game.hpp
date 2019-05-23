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
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStates();

	// Classes
	class GraphicsSettings
	{
	public:
		// Constructor / Destructor
		GraphicsSettings();
		~GraphicsSettings();

		// Functions
		void saveToFile(const std::string path);
		void loadFromFile(const std::string path);

		// Variables
		std::string title;
		sf::VideoMode resolution;
		bool fullscreen;
		bool verticalSync;
		unsigned framerateLimit;
		sf::ContextSettings contextSettings;
		std::vector<sf::VideoMode> videoModes;

	};

	// Resources
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<std::stack<std::unique_ptr<State>>> states;
	std::shared_ptr<std::map<std::string, int>> supportedKeys;
	sf::Event sfEvent;
	sf::Clock dtClock;

	GraphicsSettings graphicsSettings;

	// Variables
	float dt;

};

#endif /* GAME_HPP_ */
