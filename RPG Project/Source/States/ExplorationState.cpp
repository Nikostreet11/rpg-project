/*
 * GameState.cpp
 *
 *  Created on: Apr 9, 2019
 *      Author: nicop
 */

#include "ExplorationState.hpp"
// Static functions

// Constructors / Destructors
ExplorationState::ExplorationState(StateData& stateData) :
		State(stateData)
{
	initDeferredRendering();
	initCamera();
	initBindings();
	initFonts();
	initTextures();
	initPlayers();
	initTileMap();
	initPauseMenu();
}

ExplorationState::~ExplorationState()
{
}

// Functions
void ExplorationState::endState()
{
	std::cout << "Ending GameState" << std::endl;
	ended = true;
}

void ExplorationState::update(const float& dt)
{
	updateMousePositions(camera);
	updateInput(dt);

	if (!paused)
	{
		// Unpaused update
		updatePlayerInput(dt);
		tileMap->update(mousePosView);
		tileMap->updateBoundsCollisions(player, dt);
		tileMap->updateTilesCollisions(player, dt);
		player->update(dt);
		updateCamera(dt);
	}
	else
	{
		// Paused update
		updatePauseMenu();
	}
}

void ExplorationState::updateCamera(const float& dt)
{
	camera->setCenter(sf::Vector2f(
			std::round(player->getPosition().x + player->getSize().x / 2.f),
			std::round(player->getPosition().y + player->getSize().y / 2.f)));
}

void ExplorationState::updateInput(const float& dt)
{
	InputButton& key = keybinds.at("CLOSE");

	if (key.isPressed())
	{
		// Key pressed
		if (!paused)
			pauseState();
		else
			unpauseState();
	}

	if (key.isReleased())
	{
		// Key released
	}
}

void ExplorationState::updatePlayerInput(const float& dt)
{
	if (keybinds.at("MOVE_LEFT").isHold())
	{
		player->move(-1, 0, dt);
	}

	if (keybinds.at("MOVE_RIGHT").isHold())
	{
		player->move(1, 0, dt);
	}

	if (keybinds.at("MOVE_UP").isHold())
	{
		player->move(0, -1, dt);
	}

	if (keybinds.at("MOVE_DOWN").isHold())
	{
		player->move(0, 1, dt);
	}
}

void ExplorationState::updatePauseMenu()
{
	pauseMenu->update(mousePosWindow);
	if (pauseMenu->isButtonPressed("QUIT"))
		endState();
}

void ExplorationState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	target->setView(target->getDefaultView());

	renderTexture.clear();

	renderTexture.setView(*camera);
	tileMap->render(renderTexture);
	player->render(renderTexture);

	if (paused)
	{
		// Pause menu render
		renderTexture.setView(renderTexture.getDefaultView());
		pauseMenu->render(renderTexture);
	}

	renderTexture.display();

	target->draw(renderSprite);
}

// Getters / Setters

// Initialization functions
void ExplorationState::initDeferredRendering()
{
	renderTexture.create(
			graphicsSettings->resolution.width,
			graphicsSettings->resolution.height);

	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setTextureRect(sf::IntRect(
			0,
			0,
			graphicsSettings->resolution.width,
			graphicsSettings->resolution.height));
}

void ExplorationState::initCamera()
{
	camera = std::make_shared<sf::View>();

	camera->setSize(
			graphicsSettings->resolution.width,
			graphicsSettings->resolution.height);

	camera->setCenter(
			graphicsSettings->resolution.width / 2.f,
			graphicsSettings->resolution.height / 2.f);
}

void ExplorationState::initBindings()
{
	std::ifstream ifs("Config/Keybinds/GameState.ini");

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

	/*keybinds["CLOSE"] = supportedKeys->at("Escape");
	keybinds["MOVE_LEFT"] = supportedKeys->at("A");
	keybinds["MOVE_RIGHT"] = supportedKeys->at("D");
	keybinds["MOVE_UP"] = supportedKeys->at("W");
	keybinds["MOVE_DOWN"] = supportedKeys->at("S");*/
}

void ExplorationState::initFonts()
{
	font = std::make_shared<sf::Font>();

	if (!font->loadFromFile("Fonts/Arial.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
	}
}

void ExplorationState::initTextures()
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

void ExplorationState::initPlayers()
{
	sf::Vector2f position = {0, 0};
	player = std::make_shared<Player>(
			position,
			textures["EXPLORATION_PLAYABLE_CHARACTERS"]);
}

void ExplorationState::initTileMap()
{
	tileMap.reset(new TileMap(
			sf::Vector2u(15, 15),
			stateData.gridSize,
			"Villages.png",
			32));
	tileMap->loadFromFile("testTileMap.txt");
}

void ExplorationState::initPauseMenu()
{
	pauseMenu.reset(new gui::PauseMenu(window, font));

	pauseMenu->addButton("QUIT", 800.f, "Quit");
}
