/*
 * EditorState.cpp
 *
 *  Created on: Apr 27, 2019
 *      Author: nicop
 */

#include "EditorState.hpp"

EditorState::EditorState(
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<std::map<std::string, int>> supportedKeys,
		std::shared_ptr<std::stack<std::unique_ptr<State>>> states) :
State(window, supportedKeys, states)
{
	initVariables();
	initKeybinds();
	initFonts();
	initBackground();
	initPauseMenu();
	initButtons();

	/*addEntry("New Game", Exploration::getInstance());
	addEntry("Load Game");
	addEntry("Options");
	addEntry("Exit");*/
}

EditorState::~EditorState() {/*
	instance = nullptr;
*/}

void EditorState::endState()
{
	std::cout << "Ending EditorState" << std::endl;
	ended = true;
}

void EditorState::update(const float& dt)
{
	updateInput(dt);
	updateMousePositions();

	if (!paused)
	{
		// Unpaused update
		updateButtons();
	}
	else
	{
		// Paused update
		updatePauseMenu();
	}
}

void EditorState::updateInput(const float& dt)
{
	Key& key = keybinds.at("CLOSE");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key.code)) &&
			!key.wasPressed)
	{
		// Key pressed
		if (!paused)
			pauseState();
		else
			unpauseState();

		key.wasPressed = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key.code)) &&
			key.wasPressed)
	{
		// Key released

		key.wasPressed = false;
	}
}

void EditorState::updateButtons()
{
	/* Updates all the buttons in the state and handles their functionalities */
	for (auto &it : buttons)
	{
		it.second->update(mousePosView);
	}
}

void EditorState::updatePauseMenu()
{
	pauseMenu->update(mousePosView);

	if (pauseMenu->isButtonPressed("QUIT"))
		endState();
}

void EditorState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	map.render(target);

	renderButtons(target);

	if (paused)
	{
		// Pause menu render
		pauseMenu->render(window);
	}

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

void EditorState::renderButtons(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	for (auto &it : buttons)
	{
		it.second->render(target);
	}
}

// Initialization functions
void EditorState::initVariables()
{
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/Keybinds/EditorState.ini");

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

void EditorState::initFonts()
{
	font = std::make_shared<sf::Font>();

	if (!font->loadFromFile("Fonts/Arial.ttf"))
	{
		throw "ERROR::EDITORSTATE::COULD_NOT_LOAD_FONT";
	}
}

void EditorState::initBackground()
{
}

void EditorState::initButtons()
{
}

void EditorState::initPauseMenu()
{
	pauseMenu.reset(new PauseMenu(window, font));

	pauseMenu->addButton("QUIT", 800.f, "Quit");
}
