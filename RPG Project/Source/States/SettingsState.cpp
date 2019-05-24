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
	initGUI();
	initOptions();
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
	updateGUI(dt);
}

void SettingsState::updateInput(const float& dt)
{
}

void SettingsState::updateGUI(const float& dt)
{
	// Updates all the GUI elements in the state

	// Buttons
	for (auto &iterator : buttons)
	{
		iterator.second->update(mousePosView);
	}

	// Drop-down lists
	for (auto &iterator : dropDownLists)
	{
		iterator.second->update(mousePosView);
	}

	// Handles the GUI elements' functionalities

	// Buttons
	if (buttons["BACK"]->isPressed())
	{
		// Quit the game
		endState();
	}

	if (buttons["APPLY"]->isPressed())
	{
		// TODO: remove later
		window->create(
				videoModes[std::stoi(
						dropDownLists["RESOLUTIONS"]->getActiveKey()
						)],
				"test", sf::Style::Default);
	}

	// Drop-down lists


}

void SettingsState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	target->draw(background);

	renderGUI(target);

	// TODO: remove later
	sf::Text mouseText;
	mouseText.setPosition(mousePosView.x, mousePosView.y - 12);
	mouseText.setFont(*font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}

void SettingsState::renderGUI(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	for (auto &iterator : buttons)
	{
		iterator.second->render(target);
	}

	for (auto &iterator : dropDownLists)
	{
		iterator.second->render(target);
	}

	target->draw(options);
}

// Initialization functions
void SettingsState::initVariables()
{
	videoModes = sf::VideoMode::getFullscreenModes();
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

	if (!font->loadFromFile("Fonts/OpenSans-Regular.ttf"))
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

void SettingsState::initGUI()
{
	// Back button
	buttons["BACK"].reset(new gui::Button(
			// Position
			sf::Vector2f(1600, 100),
			// Size
			sf::Vector2f(200, 100),
			// Text options
			font, "Back", 50,
			sf::Color(150, 150, 150, 250),
			sf::Color(250, 250, 250, 250),
			sf::Color(220, 220, 220, 250),
			// Button colors
			sf::Color(150, 150, 150, 0),
			sf::Color(250, 250, 250, 0),
			sf::Color(220, 220, 220, 0)
			));

	// Apply button
	buttons["APPLY"].reset(new gui::Button(
			// Position
			sf::Vector2f(1000, 100),
			// Size
			sf::Vector2f(200, 100),
			// Text options
			font, "Apply", 50,
			sf::Color(150, 150, 150, 250),
			sf::Color(250, 250, 250, 250),
			sf::Color(220, 220, 220, 250),
			// Button colors
			sf::Color(150, 150, 150, 0),
			sf::Color(250, 250, 250, 0),
			sf::Color(220, 220, 220, 0)
			));

	// Resolution drop-down list
	std::vector<std::pair<std::string, std::string>> elements;

	int videoModesIndex = 0;
	for (auto &videoMode : videoModes)
	{
		std::string str =
				std::to_string(videoMode.width) + 'x' +
				std::to_string(videoMode.height);

		elements.push_back({std::to_string(videoModesIndex), str});
		videoModesIndex++;
	}

	dropDownLists["RESOLUTIONS"].reset(new gui::DropDownList(
			// Position
			sf::Vector2f(500, 100),
			// Size
			sf::Vector2f(300, 60),
			// Text options
			font, elements)
	);
}

void SettingsState::initOptions()
{
	options.setFont(*font);

	options.setPosition(sf::Vector2f(100.f, 100.f));

	options.setCharacterSize(50);
	options.setFillColor(sf::Color(255, 255, 255, 255));

	options.setString(
			"Resolution\n\nFullscreen\n\nVSync\n\nAntialiasing");
}

