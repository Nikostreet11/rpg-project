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

MainMenuState::MainMenuState(StateData& stateData) :
		State(stateData)
{
	initVariables();
	initBindings();
	initFonts();
	initBackground();
	initButtons();
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
		it.second->update(mousePosWindow);
	}

	// New game
	if (buttons["GAME_STATE"]->isReleased())
	{
		std::unique_ptr<State> explorationStatePtr(
				new ExplorationState(stateData));
		states->push(move(explorationStatePtr));
	}

	// Editor
	if (buttons["EDITOR_STATE"]->isReleased())
	{
		std::unique_ptr<State> editorStatePtr(
				new EditorState(stateData));
		states->push(move(editorStatePtr));
	}

	// Settings
	if (buttons["SETTINGS_STATE"]->isReleased())
	{
		std::unique_ptr<State> settingsStatePtr(
				new SettingsState(stateData));
		states->push(move(settingsStatePtr));
	}

	// Quit the game
	if (buttons["EXIT"]->isReleased())
	{
		endState();
	}
}

void MainMenuState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	target->setView(target->getDefaultView());
	target->draw(background);
	renderButtons(target);
}

void MainMenuState::renderButtons(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	for (auto &iterator : buttons)
	{
		iterator.second->render(*target);
	}
}

// Initialization functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initBindings()
{
	std::ifstream ifs("Config/Keybinds/MainMenuState.ini");

	if (ifs.is_open())
	{
		std::string action, key;

		while (ifs >> action >> key)
		{
			keybinds[action].setType(InputButton::Type::keyboardKey);
			keybinds[action].setCode((*supportedKeys)[key]);
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
	buttons["GAME_STATE"].reset(new gui::Button(
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

	buttons["EDITOR_STATE"].reset(new gui::Button(
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

	buttons["SETTINGS_STATE"].reset(new gui::Button(
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

	buttons["EXIT"].reset(new gui::Button(
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
