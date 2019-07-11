/*
 * Game.cpp
 *
 *  Created on: Jul 26, 2018
 *      Author: nicop
 */


#include "Game.hpp"

/*#include "Human.h"

#include <chrono>
#include <thread>*/

// Static functions

// Constructor / Destructor
Game::Game()/* : state(MainMenu::getInstance())*/
{
	initVariables();
	initGraphicsSettings();
	initWindow();
	initKeyboardKeys();
	initMouseButtons();
	initStates();
	initStateData();

	start();
}

Game::~Game()
{
}

// Functions
void Game::run()
{
	while (window->isOpen())
	{
		updateDt();
		update();
		render();
	}
}

void Game::close()
{
	std::cout << "Closing Game" << std::endl;

	window->close();
}

void Game::update()
{
	updateSFMLEvents();

	if (window->hasFocus())
	{
		if (!states->empty())
		{
			states->top()->update(dt);

			if (states->top()->isEnded())
			{
				states->pop();
			}
		}
		// Game end
		else
		{
			close();
		}
	}
}

void Game::updateDt()
{
	/* updates the dt variable with the time it takes to update and render one
	 * frame
	 */
	dt = dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (window->pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
			window->close();
	}
}

void Game::render()
{
	window->clear();

	// Render items
	if (!states->empty())
		states->top()->render();

	window->display();
}

// Initialization functions
void Game::initVariables()
{
	window = nullptr;
	dt = 0.f;

	gridSize = 128.f;
}

void Game::initGraphicsSettings()
{
	graphicsSettings = std::make_shared<GraphicsSettings>();
	graphicsSettings->loadFromFile("Config/Graphics.ini");
}

void Game::initWindow()
{
	/* Creates a SFML window */
	if (graphicsSettings->fullscreen)
	{
		window = std::make_shared<sf::RenderWindow>(
			graphicsSettings->resolution,
			graphicsSettings->title,
			sf::Style::Fullscreen,
			graphicsSettings->contextSettings);
	}
	else
	{
		window = std::make_shared<sf::RenderWindow>(
			graphicsSettings->resolution,
			graphicsSettings->title,
			sf::Style::Titlebar | sf::Style::Close,
			graphicsSettings->contextSettings);
	}

	window->setFramerateLimit(graphicsSettings->framerateLimit);
	window->setVerticalSyncEnabled(graphicsSettings->verticalSync);
}

void Game::initKeyboardKeys()
{
	supportedKeys = std::make_shared<std::map<std::string, int>>();

	std::ifstream ifs("Config/SupportedKeys.ini");

	if (ifs.is_open())
	{
		std::string key;
		int keyValue;

		while (ifs >> key >> keyValue)
		{
			(*supportedKeys)[key] = keyValue;
		}
	}

	ifs.close();

	// TODO: remove later
	std::cout << "Supported keyboard keys:" << std::endl;

	for (auto i : *supportedKeys)
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void Game::initMouseButtons()
{
	supportedMouseButtons = std::make_shared<std::map<std::string, int>>();

	std::ifstream ifs("Config/SupportedMouseButtons.ini");

	if (ifs.is_open())
	{
		std::string button;
		int code;

		while (ifs >> button >> code)
		{
			(*supportedMouseButtons)[button] = code;
		}
	}

	ifs.close();

	// TODO: remove later
	std::cout << "Supported mouse buttons:" << std::endl;

	for (auto i : *supportedMouseButtons)
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void Game::initStates()
{
	states = std::make_shared<std::stack<std::unique_ptr<State>>>();
}

void Game::initStateData()
{
	stateData.graphicsSettings = graphicsSettings;
	stateData.window = window;
	stateData.supportedKeys = supportedKeys;
	stateData.supportedMouseButtons = supportedMouseButtons;
	stateData.states = states;
	stateData.gridSize = gridSize;
}

void Game::start()
{
	std::unique_ptr<State> mainMenuStatePtr(new MainMenuState(stateData));

	states->push(move(mainMenuStatePtr));
}
