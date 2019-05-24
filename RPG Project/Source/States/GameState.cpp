/*
 * GameState.cpp
 *
 *  Created on: Apr 9, 2019
 *      Author: nicop
 */

#include "GameState.hpp"
// Static functions

// Constructors / Destructors
GameState::GameState(StateData& stateData) :
		State(stateData)
{
	initKeybinds();
	initFonts();
	initTextures();
	initPlayers();
	initPauseMenu();
}

GameState::~GameState()
{
}

// Functions
void GameState::endState()
{
	std::cout << "Ending GameState" << std::endl;
	ended = true;
}

void GameState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);

	if (!paused)
	{
		// Unpaused update
		updatePlayerInput(dt);

		player->update(dt);
	}
	else
	{
		// Paused update
		updatePauseMenu();
	}
}

void GameState::updateInput(const float& dt)
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

void GameState::updatePlayerInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(
			keybinds.at("MOVE_LEFT").code)))
		player->move(-1, 0, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(
			keybinds.at("MOVE_RIGHT").code)))
		player->move(1, 0, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(
			keybinds.at("MOVE_UP").code)))
		player->move(0, -1, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(
			keybinds.at("MOVE_DOWN").code)))
		player->move(0, 1, dt);
}

void GameState::updatePauseMenu()
{
	pauseMenu->update(mousePosView);
	if (pauseMenu->isButtonPressed("QUIT"))
		endState();
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	map.render(target);

	player->render(target);

	if (paused)
	{
		// Pause menu render
		pauseMenu->render(window);
	}
}

// Getters / Setters

// Initialization functions
void GameState::initKeybinds()
{
	std::ifstream ifs("Config/Keybinds/GameState.ini");

	if (ifs.is_open())
	{
		std::string action, key;

		while (ifs >> action >> key)
		{
			keybinds[action].code = (*supportedKeys)[key];
		}
	}

	ifs.close();

	/*keybinds["CLOSE"] = supportedKeys->at("Escape");
	keybinds["MOVE_LEFT"] = supportedKeys->at("A");
	keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
	keybinds["MOVE_UP"] = supportedKeys->at("W");
	keybinds["MOVE_DOWN"] = supportedKeys->at("S");*/
}

void GameState::initFonts()
{
	font = std::make_shared<sf::Font>();

	if (!font->loadFromFile("Fonts/Arial.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
	}
}

void GameState::initTextures()
{
	textures["EXPLORATION_PLAYABLE_CHARACTERS"] =
			std::make_shared<sf::Texture>();

	if (!textures["EXPLORATION_PLAYABLE_CHARACTERS"]->loadFromFile(
			"Images/Exploration/Characters/PlayableCharacters.png"/*,
			sf::IntRect(
					sf::Vector2i(0, 0),
					sf::Vector2i(36, 36)
					)*/
			))
	{
		throw "ERROR::GAMESTATE::UNABLE_TO_LOAD_PLAYER_TEXTURE";
	}
}

void GameState::initPlayers()
{
	sf::Vector2f position = {0, 0};
	player.reset(new Player(position, textures["EXPLORATION_PLAYABLE_CHARACTERS"]));
}

void GameState::initPauseMenu()
{
	pauseMenu.reset(new PauseMenu(window, font));

	pauseMenu->addButton("QUIT", 800.f, "Quit");
}
