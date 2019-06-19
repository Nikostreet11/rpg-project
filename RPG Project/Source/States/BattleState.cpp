/*
 * BattleState.cpp
 *
 *  Created on: Jun 16, 2019
 *      Author: Nikostreet11
 */

#include "BattleState.hpp"

// Constructor / Destructor
BattleState::BattleState(StateData& stateData) :
		State(stateData)
{
	initDeferredRendering();
	initBindings();
	initFonts();
	initTextures();
	initBackground();
	initPauseMenu();
}

BattleState::~BattleState()
{
}

// Functions
void BattleState::endState()
{
	std::cout << "Ending BattleState" << std::endl;
	ended = true;
}

void BattleState::update(const float& dt)
{
	updateMousePositions();
	updateInput(dt);

	if (!paused)
	{
		// Unpaused update
	}
	else
	{
		// Paused update
		updatePauseMenu();
	}
}

void BattleState::updateInput(const float& dt)
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

void BattleState::updatePauseMenu()
{
	pauseMenu->update(mousePosWindow);

	if (pauseMenu->isButtonPressed("QUIT"))
		endState();
}

void BattleState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	target->setView(target->getDefaultView());

	renderTexture.clear();

	renderTexture.draw(background);

	if (paused)
	{
		// Pause menu render
		renderTexture.setView(renderTexture.getDefaultView());
		pauseMenu->render(renderTexture);
	}

	renderTexture.display();

	target->draw(renderSprite);
}

void BattleState::initDeferredRendering()
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

void BattleState::initBindings()
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

void BattleState::initFonts()
{
	font = std::make_shared<sf::Font>();

	if (!font->loadFromFile("Fonts/Arial.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD_NOT_LOAD_FONT");
	}
}

void BattleState::initTextures()
{
	textures["BACKGROUNDS"] = std::make_shared<sf::Texture>();

	if (!textures["BACKGROUNDS"]->loadFromFile(
			"Images/Battle/Backgrounds/Backgrounds.png"))
	{
		throw "ERROR::BATTLESTATE::UNABLE_TO_LOAD_BACKGROUND_TEXTURE";
	}

	textures["WARRIOR"] = std::make_shared<sf::Texture>();

	if (!textures["WARRIOR"]->loadFromFile(
			"Images/Battle/Characters/Warrior.png"))
	{
		throw "ERROR::BATTLESTATE::UNABLE_TO_LOAD_WARRIOR_TEXTURE";
	}

	textures["FOES"] = std::make_shared<sf::Texture>();

	if (!textures["FOES"]->loadFromFile(
			"Images/Battle/Enemies/Foes.png"))
	{
		throw "ERROR::BATTLESTATE::UNABLE_TO_LOAD_FOES_TEXTURE";
	}
}

void BattleState::initBackground()
{
	background.setTexture(*textures["BACKGROUNDS"]);
	background.setTextureRect(sf::IntRect(
			2,
			2 * 15 + 312 * 7,
			512,
			312));
	background.setScale(
			graphicsSettings->resolution.width / 512.f,
			graphicsSettings->resolution.height / 312.f);
}

void BattleState::initPauseMenu()
{
	pauseMenu.reset(new gui::PauseMenu(window, font));

	pauseMenu->addButton("QUIT", 800.f, "Quit");
}
