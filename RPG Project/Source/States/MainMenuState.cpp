/*
 * MainMenu.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: nicop
 */

#include "MainMenuState.hpp"

/*#include "Exploration.h"
#include "../GraphicEngine.h"
#include "../ServiceLocator.h"

#include <iostream>*/

//MainMenu* MainMenu::instance = nullptr;

MainMenuState::MainMenuState(
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<std::map<std::string, int>> supportedKeys,
		std::shared_ptr<std::stack<std::unique_ptr<State>>> states) :
State(window, supportedKeys, states)
{
	initVariables();
	initKeybinds();
	initFonts();
	initBackground();
	initButtons();

	/*addEntry("New Game", Exploration::getInstance());
	addEntry("Load Game");
	addEntry("Options");
	addEntry("Exit");*/
}

MainMenuState::~MainMenuState() {/*
	instance = nullptr;
*/}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState" << std::endl;
	ended = true;
}

void MainMenuState::update(const float& dt)
{
	updateInput(dt);
	updateMousePositions();
	updateButtons();
}

void MainMenuState::updateInput(const float& dt)
{
}

void MainMenuState::updateButtons()
{
	/* Updates all the buttons in the state and handles their functionalities */
	for (auto &it : buttons)
	{
		it.second->update(mousePosView);
	}

	// New game
	if (buttons["GAME_STATE"]->isPressed())
	{
		std::unique_ptr<State> gameStatePtr(
				new GameState(window, supportedKeys, states));
		states->push(move(gameStatePtr));
	}

	// New game
	if (buttons["EDITOR_STATE"]->isPressed())
	{
		std::unique_ptr<State> editorStatePtr(
				new EditorState(window, supportedKeys, states));
		states->push(move(editorStatePtr));
	}

	// Quit the game
	if (buttons["EXIT"]->isPressed())
	{
		endState();
	}
}

void MainMenuState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	target->draw(background);
	renderButtons(target);

	// TODO: remove later
	/*sf::Text mouseText;
	mouseText.setPosition(mousePosView.x, mousePosView.y - 12);
	mouseText.setFont(*font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}

void MainMenuState::renderButtons(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	for (auto &it : buttons)
	{
		it.second->render(target);
	}
}

/*MainMenu* MainMenu::getInstance() {
	if (instance == nullptr) {
		instance = new MainMenu();
	}
	return instance;
}*/

/*void MainMenu::draw() {
	GraphicService* graphicService = ServiceLocator::getGraphicService();
	graphicService->drawMainMenu(this);
}

void MainMenu::keyPressed_W(Game& game) {
	shiftBackwardActive();
}

void MainMenu::keyPressed_A(Game& game) {}

void MainMenu::keyPressed_S(Game& game) {
	shiftForwardActive();
}

void MainMenu::keyPressed_D(Game& game) {}

void MainMenu::keyPressed_Enter(Game& game) {
	entriesList.at(activeEntry)->action(game);
}*/

// Initialization functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs("Config/Keybinds/MainMenuState.ini");

	if (ifs.is_open())
	{
		std::string action, key;

		while (ifs >> action >> key)
		{
			keybinds[action] = (*supportedKeys)[key];
		}
	}

	ifs.close();
}

void MainMenuState::initFonts()
{
	font = std::make_shared<sf::Font>();

	if (!font->loadFromFile("Fonts/Arial.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
	}
}

void MainMenuState::initBackground()
{
	background.setSize(sf::Vector2f(
			window->getSize().x,
			window->getSize().y));

	if (!backgroundTexture.loadFromFile(
			"Images/MainMenu/Background.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_IMAGE";
	}

	background.setTexture(&backgroundTexture);
}

void MainMenuState::initButtons()
{
	buttons["GAME_STATE"].reset(new Button(
			// Position
			sf::Vector2f(100, 100),
			// Size
			sf::Vector2f(400, 100),
			// Text options
			font, "New Game", 50,
			sf::Color(150, 150, 150, 250),
			sf::Color(250, 250, 250, 250),
			sf::Color(220, 220, 220, 250),
			// Button colors
			sf::Color(150, 150, 150, 0),
			sf::Color(250, 250, 250, 0),
			sf::Color(220, 220, 220, 0)
			));

	buttons["EDITOR_STATE"].reset(new Button(
			// Position
			sf::Vector2f(100, 225),
			// Size
			sf::Vector2f(400, 100),
			// Text options
			font, "Editor", 50,
			sf::Color(150, 150, 150, 250),
			sf::Color(250, 250, 250, 250),
			sf::Color(220, 220, 220, 250),
			// Button colors
			sf::Color(150, 150, 150, 0),
			sf::Color(250, 250, 250, 0),
			sf::Color(220, 220, 220, 0)
			));

	buttons["SETTINGS_STATE"].reset(new Button(
			// Position
			sf::Vector2f(100, 350),
			// Size
			sf::Vector2f(400, 100),
			// Text options
			font, "Settings", 50,
			sf::Color(150, 150, 150, 250),
			sf::Color(250, 250, 250, 250),
			sf::Color(220, 220, 220, 250),
			// Button colors
			sf::Color(150, 150, 150, 0),
			sf::Color(250, 250, 250, 0),
			sf::Color(220, 220, 220, 0)
			));

	buttons["EXIT"].reset(new Button(
			// Position
			sf::Vector2f(100, 475),
			// Size
			sf::Vector2f(400, 100),
			// Text options
			font, "Quit", 50,
			sf::Color(150, 150, 150, 250),
			sf::Color(250, 250, 250, 250),
			sf::Color(220, 220, 220, 250),
			// Button colors
			sf::Color(150, 150, 150, 0),
			sf::Color(250, 250, 250, 0),
			sf::Color(220, 220, 220, 0)
			));
}
