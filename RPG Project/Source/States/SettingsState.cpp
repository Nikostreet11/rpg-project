/*
 * SettingsState.cpp
 *
 *  Created on: May 10, 2019
 *      Author: nicop
 */

#include "SettingsState.hpp"

SettingsState::SettingsState(
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
}

SettingsState::~SettingsState()
{
}

void SettingsState::endState()
{
	std::cout << "Ending SettingsState" << std::endl;
	ended = true;
}

void SettingsState::update(const float& dt)
{
	updateInput(dt);
	updateMousePositions();
	updateButtons();
}

void SettingsState::updateInput(const float& dt)
{
}

void SettingsState::updateButtons()
{
	/* Updates all the buttons in the state and handles their functionalities */
	for (auto &it : buttons)
	{
		it.second->update(mousePosView);
	}

	// Quit the game
	if (buttons["EXIT"]->isPressed())
	{
		endState();
	}
}

void SettingsState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	target->draw(background);
	renderButtons(target);
}

void SettingsState::renderButtons(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	for (auto &it : buttons)
	{
		it.second->render(target);
	}
}

// Initialization functions
void SettingsState::initVariables()
{
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/Keybinds/MainMenuState.ini");

	if (ifs.is_open())
	{
		std::string action, key;

		while (ifs >> action >> key)
		{
			keybinds[action].code = (*supportedKeys)[key];
		}
	}

	ifs.close();
}

void SettingsState::initFonts()
{
	font = std::make_shared<sf::Font>();

	if (!font->loadFromFile("Fonts/Arial.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
	}
}

void SettingsState::initBackground()
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

void SettingsState::initButtons()
{
	buttons["EXIT"].reset(new Button(
			// Position
			sf::Vector2f(300, 175),
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

