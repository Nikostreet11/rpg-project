/*
 * EditorState.cpp
 *
 *  Created on: Apr 27, 2019
 *      Author: nicop
 */

#include "EditorState.hpp"

EditorState::EditorState(StateData& stateData) :
		State(stateData)
{
	initVariables();
	initKeybinds();
	initFonts();
	initText();
	initBackground();
	initTileMap();
	initPauseMenu();
	initGUI();
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
		updateGUI();
		updateButtons();
		updateEditorInput();
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

void EditorState::updateEditorInput()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		tileMap->addTile(sf::Vector2u(mousePosGrid.x, mousePosGrid.y), 0);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		tileMap->removeTile(sf::Vector2u(mousePosGrid.x, mousePosGrid.y), 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		tileMap->selectNextTile();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		tileMap->selectPreviousTile();
	}
}

void EditorState::updateGUI()
{
	selectorRect.setTexture(&tileMap->getTileSheet());
	selectorRect.setTextureRect(tileMap->getTileRect());
	selectorRect.setPosition(
			mousePosGrid.x * gridSize,
			mousePosGrid.y * gridSize);

	std::stringstream ss;
	ss << mousePosView.x << " " << mousePosView.y << '\n';
	cursorText.setString(ss.str());
	cursorText.setPosition(mousePosView.x, mousePosView.y - 20.f);
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

	tileMap->render(target);

	renderGUI(target);
	renderButtons(target);

	if (paused)
	{
		// Pause menu render
		pauseMenu->render(window);
	}
}

void EditorState::renderGUI(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	target->draw(selectorRect);
	target->draw(cursorText);
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
	/*textureRect = sf::IntRect(
			0,
			0,
			static_cast<int>(gridSize),
			static_cast<int>(gridSize));*/
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

void EditorState::initText()
{
	cursorText.setFont(*font);
	cursorText.setCharacterSize(16);
	cursorText.setFillColor(sf::Color::White);
}

void EditorState::initBackground()
{
}

void EditorState::initTileMap()
{
	tileMap.reset(new TileMap(sf::Vector2u(20, 15), stateData.gridSize));
}

void EditorState::initPauseMenu()
{
	pauseMenu.reset(new PauseMenu(window, font));

	pauseMenu->addButton("QUIT", 800.f, "Quit");
}

void EditorState::initGUI()
{
	selectorRect.setSize(sf::Vector2f(stateData.gridSize, stateData.gridSize));

	selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::Green);
}

void EditorState::initButtons()
{
}
