/*
 * BattleState.cpp
 *
 *  Created on: Jun 16, 2019
 *      Author: Nikostreet11
 */

#include "BattleState.hpp"

// Constructor / Destructor
BattleState::BattleState(
		StateData& stateData/*,
		std::vector<std::shared_ptr<Character>> party,
		std::vector<std::shared_ptr<Character>> enemies*/) :
		State(stateData)/*,
		party(party),
		enemies(enemies)*/
{
	initVariables();
	initDeferredRendering();
	initBindings();
	initFonts();
	initTextures();
	initBackground();
	initCharacters();
	initDialogueMenu();
	initActionMenu(Empty);
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
		updateBattleInput(dt);
		//dialogueMenu->update();
		//actionMenu->update();
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

void BattleState::updateBattleInput(const float& dt)
{
	switch (phase)
	{

	case InitialPhase:

		if (keybinds["CONFIRM"].isPressed())
		{
			dialogueMenu->setNextLine();

			if (dialogueMenu->isEnded())
			{
				changePhase(ActionSelect);
			}
		}
		break;

	case ActionSelect:

		if (keybinds["CONFIRM"].isPressed())
		{
			updateActionMenu(actionMenu->getSelectedEntry());
		}

		if (keybinds["SELECT_UP"].isPressed())
		{
			actionMenu->moveMarker(Direction::Up);
		}

		if (keybinds["SELECT_LEFT"].isPressed())
		{
			actionMenu->moveMarker(Direction::Left);
		}

		if (keybinds["SELECT_DOWN"].isPressed())
		{
			actionMenu->moveMarker(Direction::Down);
		}

		if (keybinds["SELECT_RIGHT"].isPressed())
		{
			actionMenu->moveMarker(Direction::Right);
		}
		break;

	case TargetSelect:

		if (keybinds["CONFIRM"].isPressed())
		{
			changePhase(ActionResults);
		}
		break;

	case ActionResults:

		if (keybinds["CONFIRM"].isPressed())
		{
			changePhase(ActionSelect);
		}
		break;

	case EndPhase:

		if (keybinds["CONFIRM"].isPressed())
		{
			endState();
		}
		break;
	}
}

void BattleState::updateActionMenu(const std::string& entry)
{
	if (entry == "ATTACK")
	{
		changePhase(TargetSelect);
	}
	else if (entry == "MAGIC")
	{
		initActionMenu(MagicMenu);
	}
	else if (entry == "OBJECT")
	{
		initActionMenu(ObjectMenu);
	}
	else if (entry == "FLEE")
	{
		endState();
	}
	else
	{
		changePhase(TargetSelect);
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
	renderCharacters(renderTexture);
	dialogueMenu->render(renderTexture);

	// TODO: remove later
	sf::Text hoverText;
	hoverText.setFont(*font);
	hoverText.setCharacterSize(70);
	hoverText.setFillColor(sf::Color::White);
	hoverText.setPosition(
			0,
			(graphicsSettings->resolution.height - 70 * 1.3f) / 2.f);

	switch (phase)
	{
	case InitialPhase:
		break;

	case ActionSelect:
		actionMenu->render(renderTexture);
		break;

	case TargetSelect:
		hoverText.setString("TARGET SELECT PHASE");
		hoverText.setPosition(
				(graphicsSettings->resolution.width
						- hoverText.getGlobalBounds().width) / 2.f,
				hoverText.getPosition().y);
		actionMenu->render(renderTexture);
		renderTexture.draw(hoverText);
		break;

	case ActionResults:
		hoverText.setString("ACTION RESULTS PHASE");
		hoverText.setPosition(
				(graphicsSettings->resolution.width
						- hoverText.getGlobalBounds().width) / 2.f,
				hoverText.getPosition().y);
		renderTexture.draw(hoverText);
		break;

	case EndPhase:
		hoverText.setString("END PHASE");
		hoverText.setPosition(
				(graphicsSettings->resolution.width
						- hoverText.getGlobalBounds().width) / 2.f,
				hoverText.getPosition().y);
		renderTexture.draw(hoverText);
		break;

	}

	if (paused)
	{
		// Pause menu render
		pauseMenu->render(renderTexture);
	}

	renderTexture.display();

	target->draw(renderSprite);
}

void BattleState::renderCharacters(sf::RenderTarget& target)
{
	for (auto &enemy : enemies)
	{
		enemy->render(target);
	}

	for (auto &hero : party)
	{
		hero->render(target);
	}
}

// Internal
void BattleState::changePhase(Phase phase)
{
	switch (phase)
	{

	case InitialPhase:
		initActionMenu(Empty);
		break;

	case ActionSelect:
		initActionMenu(MainActions);
		break;

	case TargetSelect:
		// TODO
	case ActionResults:
		// TODO
		break;

	case EndPhase:
		endState();
	}

	this->phase = phase;
}

// Initialization
void BattleState::initVariables()
{
	phase = BattleState::InitialPhase;
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
	std::ifstream ifs("Config/Keybinds/BattleState.ini");

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

void BattleState::initCharacters()
{
	sf::Vector2f leftStart(700.f, 180.f);
	sf::Vector2f leftStep(-80.f, 100.f);

	for (size_t index = 0; index < 8; index++)
	{
		enemies.push_back(std::move(std::make_shared<Monster>(
			sf::Vector2f(
					leftStart.x + leftStep.x * index,
					leftStart.y + leftStep.y * (index % 4)),
			sf::Vector2f(200, 200),
			*textures["FOES"],
			Monster::WargWolf)));
	}

	sf::Vector2f rightStart(1200, 200);
	sf::Vector2f rightStep(80, 100);

	for (std::size_t index = 0; index < 4; index++)
	{
		party.push_back(std::move(std::make_shared<Character>(
			sf::Vector2f(
					rightStart.x + rightStep.x * index,
					rightStart.y + rightStep.y * (index % 4)),
			sf::Vector2f(180, 180),
			*textures["WARRIOR"])));
	}
}

void BattleState::initDialogueMenu()
{
	std::vector<std::string> startDialogue =
			{"Wild foes appeared!",
			"Battle starts!!!"};\

	dialogueMenu.reset(new gui::Dialogue(
			{1000, 270},
			{40, 50},
			50,
			startDialogue,
			font));

	dialogueMenu->setPosition(100, 700);
}

void BattleState::initActionMenu(ActionMenu menu)
{
	actionMenu.reset(new gui::Selection(
			sf::Vector2f(1200, 700),
			sf::Vector2f(600, 270),
			sf::Vector2f(40, 50),
			sf::Vector2u(2, 3),
			sf::Vector2u(2, 2),
			50,
			font));

	switch (menu)
	{

	case Empty:
		break;

	case MainActions:
		actionMenu->addEntry("ATTACK");
		actionMenu->addEntry("MAGIC");
		actionMenu->addEntry("OBJECT");
		actionMenu->addEntry("FLEE");
		break;

	case MagicMenu:
		actionMenu->addEntry("FIRE");
		actionMenu->addEntry("BLIZZARD");
		actionMenu->addEntry("THUNDER");
		actionMenu->addEntry("AERO");
		actionMenu->addEntry("CURE");
		actionMenu->addEntry("HEAL");
		break;

	case ObjectMenu:
		actionMenu->addEntry("POTION");
		actionMenu->addEntry("ETHER");
		actionMenu->addEntry("PHOENIX DOWN");
		actionMenu->addEntry("ANTIDOTE");
		actionMenu->addEntry("MEGAPOTION");
		actionMenu->addEntry("MEGAETHER");
		break;
	}
}

void BattleState::initPauseMenu()
{
	pauseMenu.reset(new gui::PauseMenu(window, font));

	pauseMenu->addButton("QUIT", 800.f, "Quit");
}
