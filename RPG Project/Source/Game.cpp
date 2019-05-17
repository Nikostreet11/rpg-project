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

/*void Game::start() {
	GraphicEngine graphicEngine;

	// the service locator provides a set of object oriented services to the game,
	// like graphics, audio, ecc, using a global point of access
	ServiceLocator::initialize();
	ServiceLocator::provideGraphicService(&graphicEngine);

	graphicEngine.getWindow().setFramerateLimit(15);

	// game loop
	sf::Event event;
	while (graphicEngine.getWindow().isOpen()) {
		while(graphicEngine.getWindow().pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				graphicEngine.getWindow().close();
			}
		}

		manageInput();

		graphicEngine.getWindow().clear();
		state->draw();
		graphicEngine.getWindow().display();
	}
}

void Game::manageInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		state->keyPressed_W(*this);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		state->keyPressed_A(*this);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		state->keyPressed_S(*this);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		state->keyPressed_D(*this);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		state->keyPressed_Enter(*this);
	}
}

void Game::changeState(State* newState) {
	state = newState;
}*/

// Initialization functions
void Game::initVariables()
{
	window = nullptr;
	fullscreen = false;
	dt = 0.f;
}

void Game::initWindow()
{
	std::ifstream ifs("Config/Window.ini");
	videomodes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode windowBounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framerateLimit = 60;
	bool verticalSyncEnabled = false;
	unsigned antialiasingLevel = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> windowBounds.width >> windowBounds.height;
		ifs >> fullscreen;
		ifs >> framerateLimit;
		ifs >> verticalSyncEnabled;
		ifs >> antialiasingLevel;
	}

	ifs.close();

	this->fullscreen = fullscreen;
	windowSettings.antialiasingLevel = antialiasingLevel;

	/* Creates a SFML window using options from a window.ini file. */
	if (this->fullscreen)
		window = std::make_shared<sf::RenderWindow>(
			windowBounds, title, sf::Style::Fullscreen, windowSettings);
	else
		window = std::make_shared<sf::RenderWindow>(
			windowBounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	window->setFramerateLimit(framerateLimit);
	window->setVerticalSyncEnabled(verticalSyncEnabled);
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
