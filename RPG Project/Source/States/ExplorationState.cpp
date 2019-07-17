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
	initVariables();
	initDeferredRendering();
	initCamera();
	initBindings();
	initFonts();
	initTextures();
	initParty();
	initPlayers();
	initTileMap();
	initStatsMenu();
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

		checkForBattle(dt);

		if (isGameOver())
		{
			endState();
		}
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
	if (keybinds.at("PAUSE").isPressed())
	{
		// Key pressed
		if (!paused)
			pauseState();
		else
			unpauseState();
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
	tileMap->render(renderTexture, Tile::Closeness::Background);
	player->render(renderTexture);
	tileMap->render(renderTexture, Tile::Closeness::Foreground);

	renderTexture.setView(renderTexture.getDefaultView());
	statsMenu->render(renderTexture);

	if (paused)
	{
		// Pause menu render
		pauseMenu->render(renderTexture);
	}

	renderTexture.display();

	target->draw(renderSprite);
}

// Internal
void ExplorationState::checkForBattle(const float& dt)
{
	if (battleImmunityTimer < battleImmunity)
	{
		battleImmunityTimer += dt;
	}
	else if (tileMap->isDangerousAt(player->getGlobalBounds()))
	{
		Randomizer& rand = Randomizer::getInstance();

		if (rand.percentageOn(20.f * dt))
		{
			std::unique_ptr<State> battleStatePtr(
					new BattleState(stateData, party,
							tileMap->getFoes(),
							tileMap->getBackground()));
			states->push(move(battleStatePtr));

			battleImmunityTimer = 0.f;
		}
	}
}

bool ExplorationState::isGameOver()
{
	bool gameOver = true;

	for (auto& hero : party)
	{
		if (hero->getHealth() > 0)
		{
			gameOver = false;
		}
	}

	return gameOver;
}

// Initialization functions
void ExplorationState::initVariables()
{
	battleImmunityTimer = 0.f;
	battleImmunity = 3.f;
}

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
			"Images/Exploration/Characters/PlayableCharacters.png"))
	{
		throw "ERROR::GAMESTATE::UNABLE_TO_LOAD_PLAYER_TEXTURE";
	}

	textures["WARRIOR"] = std::make_shared<sf::Texture>();

	if (!textures["WARRIOR"]->loadFromFile(
			"Images/Battle/Characters/Warrior.png"))
	{
		throw "ERROR::BATTLESTATE::UNABLE_TO_LOAD_WARRIOR_TEXTURE";
	}

	textures["THIEF"] = std::make_shared<sf::Texture>();

	if (!textures["THIEF"]->loadFromFile(
			"Images/Battle/Characters/Thief.png"))
	{
		throw "ERROR::BATTLESTATE::UNABLE_TO_LOAD_THIEF_TEXTURE";
	}

	textures["BLACK_MAGE"] = std::make_shared<sf::Texture>();

	if (!textures["BLACK_MAGE"]->loadFromFile(
			"Images/Battle/Characters/BlackMage.png"))
	{
		throw "ERROR::BATTLESTATE::UNABLE_TO_LOAD_BLACK_MAGE_TEXTURE";
	}

	textures["WHITE_MAGE"] = std::make_shared<sf::Texture>();

	if (!textures["WHITE_MAGE"]->loadFromFile(
			"Images/Battle/Characters/WhiteMage.png"))
	{
		throw "ERROR::BATTLESTATE::UNABLE_TO_LOAD_WHITE_MAGE_TEXTURE";
	}

	textures["MONSTERS"] = std::make_shared<sf::Texture>();

	if (!textures["MONSTERS"]->loadFromFile(
			"Images/Battle/Enemies/Foes.png"))
	{
		throw "ERROR::BATTLESTATE::UNABLE_TO_LOAD_FOES_TEXTURE";
	}

	textures["ICONS"] = std::make_shared<sf::Texture>();

	if (!textures["ICONS"]->loadFromFile(
			"Images/Battle/Icons/Icons.png"))
	{
		throw "ERROR::BATTLESTATE::UNABLE_TO_LOAD_ICONS_TEXTURE";
	}

	textures["STATS"] = std::make_shared<sf::Texture>();

	if (!textures["STATS"]->loadFromFile(
			"Images/Battle/Icons/Stats.png"))
	{
		throw "ERROR::BATTLESTATE::UNABLE_TO_LOAD_STATS_TEXTURE";
	}
}

void ExplorationState::initParty()
{
	party.clear();

	party.push_back(std::move(std::make_shared<Human>(
			Human::Warrior, textures)));
	party.push_back(std::move(std::make_shared<Human>(
			Human::Thief, textures)));
	party.push_back(std::move(std::make_shared<Human>(
			Human::WhiteMage, textures)));
	party.push_back(std::move(std::make_shared<Human>(
			Human::BlackMage, textures)));
}

void ExplorationState::initPlayers()
{
	sf::Vector2f position = {2425, 2500};
	player = std::make_shared<Player>(
			position,
			textures["EXPLORATION_PLAYABLE_CHARACTERS"]);
}

void ExplorationState::initTileMap()
{
	tileMap.reset(new DefaultMap(
			sf::Vector2u(15, 15), 3,
			stateData.gridSize,
			"Villages.png",
			32,
			textures,
			font));
	tileMap->loadFromFile("testTileMap.txt");
}

void ExplorationState::initStatsMenu()
{
	statsMenu = std::make_shared<gui::StatsMenu>(
			sf::Vector2f(1200.f, 20.f),
			textures,
			font);

	for (auto& hero : party)
	{
		statsMenu->addSubject(hero);
	}

	statsMenu->update();
}

void ExplorationState::initPauseMenu()
{
	pauseMenu.reset(new gui::PauseMenu(window, font));

	pauseMenu->addButton("QUIT", 800.f, "Quit");
}
