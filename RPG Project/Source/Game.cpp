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
	initKeys();
	initStates();
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

void Game::updateDt()
{
	/* updates the dt variable with the time it takes to update and render one
	 * frame */
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
}

void Game::initGraphicsSettings()
{
	graphicsSettings.loadFromFile("Config/Graphics.ini");
}

void Game::initWindow()
{
	/* Creates a SFML window */
	if (graphicsSettings.fullscreen)
	{
		window = std::make_shared<sf::RenderWindow>(
			graphicsSettings.resolution,
			graphicsSettings.title,
			sf::Style::Fullscreen,
			graphicsSettings.contextSettings);
	}
	else
	{
		window = std::make_shared<sf::RenderWindow>(
			graphicsSettings.resolution,
			graphicsSettings.title,
			sf::Style::Titlebar | sf::Style::Close,
			graphicsSettings.contextSettings);
	}

	window->setFramerateLimit(graphicsSettings.framerateLimit);
	window->setVerticalSyncEnabled(graphicsSettings.verticalSync);
}

void Game::initKeys()
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
	for (auto i : *supportedKeys)
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void Game::initStates()
{
	states = std::make_shared<std::stack<std::unique_ptr<State>>>();
	std::unique_ptr<State> mainMenuStatePtr(
			new MainMenuState(window, supportedKeys, states));
	states->push(move(mainMenuStatePtr));
}

// ::::::::::::::::::::GraphicsSettings::::::::::::::::::::

// Constructor / Destructor
Game::GraphicsSettings::GraphicsSettings()
{
	title = "DEFAULT";
	resolution = sf::VideoMode::getDesktopMode();
	fullscreen = false;
	verticalSync = false;
	framerateLimit = 120;
	contextSettings.antialiasingLevel = 0;
	videoModes = sf::VideoMode::getFullscreenModes();
}

Game::GraphicsSettings::~GraphicsSettings()
{

}

// Functions
void Game::GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << title;
		ofs << resolution.width << " " << resolution.height;
		ofs << fullscreen;
		ofs << framerateLimit;
		ofs << verticalSync;
		ofs << contextSettings.antialiasingLevel;
	}

	ofs.close();
}

void Game::GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> resolution.width >> resolution.height;
		ifs >> fullscreen;
		ifs >> framerateLimit;
		ifs >> verticalSync;
		ifs >> contextSettings.antialiasingLevel;
	}

	ifs.close();
}
