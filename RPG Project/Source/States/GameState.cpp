/*
 * GameState.cpp
 *
 *  Created on: Apr 9, 2019
 *      Author: nicop
 */

#include "GameState.hpp"
// Static functions

// Constructors / Destructors
GameState::GameState(
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<std::map<std::string, int>> supportedKeys,
		std::shared_ptr<std::stack<std::unique_ptr<State>>> states) :
State(window, supportedKeys, states),
pauseMenu(window)
{
	initKeybinds();
	initTextures();
	initPlayers();
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
	if (!paused)
	{
		// Unpaused update
		updateInput(dt);
		updateMousePositions();

		player->update(dt);
	}
	else
	{
		// Paused update
		pauseMenu.update(dt);
	}
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
		player->move(-1, 0, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
		player->move(1, 0, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
		player->move(0, -1, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
		player->move(0, 1, dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
	{
		if (!paused)
			pauseState();
		/*else
			unpauseState();*/
	}
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	player->render(target);

	if (paused)
	{
		// Pause menu render
		pauseMenu.render(window);
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
			keybinds[action] = (*supportedKeys)[key];
		}
	}

	ifs.close();

	/*keybinds["CLOSE"] = supportedKeys->at("Escape");
	keybinds["MOVE_LEFT"] = supportedKeys->at("A");
	keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
	keybinds["MOVE_UP"] = supportedKeys->at("W");
	keybinds["MOVE_DOWN"] = supportedKeys->at("S");*/
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
