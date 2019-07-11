/*
 * BattleState.cpp
 *
 *  Created on: Jun 16, 2019
 *      Author: Nikostreet11
 */

#include "BattleState.hpp"

// Constructor / Destructor
BattleState::BattleState(
		StateData& stateData,
		std::vector<std::shared_ptr<Character>> party,
		std::vector<std::shared_ptr<Character>> enemies) :
	State(stateData),
	party(party),
	enemies(enemies)
{
	initVariables();
	initDeferredRendering();
	initBindings();
	initFonts();
	initTextures();
	initBackground();
	initCharacters();
	initActiveQueue();
	initDialogueMenu();
	initActionMenu(Empty);
	initPauseMenu();
	initMarkers();
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
		updateCharacters(dt);
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

	case Begin:

		updateBegin(dt);
		break;

	case ActionSelection:
		updateActionSelection(dt);
		break;

	case TargetSelection:
		updateTargetSelection(dt);
		break;

	case Results:

		updateResults(dt);
		break;

	case End:

		updateEnd(dt);
		break;
	}
}

void BattleState::updateBegin(const float& dt)
{
	if (keybinds["CONFIRM"].isPressed())
	{
		dialogueMenu->setNextLine();

		if (dialogueMenu->isEnded())
		{
			changePhase(ActionSelection);
		}
	}
}

void BattleState::updateActionSelection(const float& dt)
{
	if (active->hasStrategy())
	{
		action = active->chooseAction();
		changePhase(TargetSelection);
	}
	else
	{
		if (keybinds["CONFIRM"].isPressed())
		{
			std::string entry = actionMenu->getSelectedEntry();

			if (entry == "Magic" || entry == "Object")
			{
				updateActionMenu(entry);
			}
			else if (entry == "Flee")
			{
				triedToFlee = true;
				changePhase(Results);
			}
			else
			{
				action = active->getAction(entry);
				changePhase(TargetSelection);
			}
		}

		if (keybinds["SELECT_UP"].isPressed())
		{
			actionMenu->moveMarker(Direction::Up);
			initDialogueMenu();
		}

		if (keybinds["SELECT_LEFT"].isPressed())
		{
			actionMenu->moveMarker(Direction::Left);
			initDialogueMenu();
		}

		if (keybinds["SELECT_DOWN"].isPressed())
		{
			actionMenu->moveMarker(Direction::Down);
			initDialogueMenu();
		}

		if (keybinds["SELECT_RIGHT"].isPressed())
		{
			actionMenu->moveMarker(Direction::Right);
			initDialogueMenu();
		}
	}
}

void BattleState::updateTargetSelection(const float& dt)
{
	if (active->hasStrategy())
	{
		target = active->chooseTarget(enemies, party);

		targetMarker.setPosition(target->getPosition());
		targetMarker.move(
				target->getSize().x / 2.f - targetMarker.getSize() / 2,
				-targetMarker.getSize() * 0.8f);

		changePhase(Results);
	}
	else
	{
		if (keybinds["CONFIRM"].isPressed())
		{
			target = targets[actionMenu->getIndex()];
			changePhase(Results);
		}

		if (keybinds["SELECT_UP"].isPressed())
		{
			actionMenu->moveMarker(Direction::Up);
			updateTargetMarkerPosition();
		}

		if (keybinds["SELECT_LEFT"].isPressed())
		{
			actionMenu->moveMarker(Direction::Left);
			updateTargetMarkerPosition();
		}

		if (keybinds["SELECT_DOWN"].isPressed())
		{
			actionMenu->moveMarker(Direction::Down);
			updateTargetMarkerPosition();
		}

		if (keybinds["SELECT_RIGHT"].isPressed())
		{
			actionMenu->moveMarker(Direction::Right);
			updateTargetMarkerPosition();
		}
	}
}

void BattleState::updateResults(const float& dt)
{
	if (keybinds["CONFIRM"].isPressed())
	{
		dialogueMenu->setNextLine();

		if (dialogueMenu->isEnded())
		{
			if (outcome == None)
			{
				changePhase(ActionSelection);
			}
			else
			{
				changePhase(End);
			}
		}
	}
}

void BattleState::updateEnd(const float& dt)
{
	if (keybinds["CONFIRM"].isPressed())
	{
		dialogueMenu->setNextLine();

		if (dialogueMenu->isEnded())
		{
			endState();
		}
	}
}

void BattleState::updateTargetMarkerPosition()
{
	size_t index = actionMenu->getIndex();
	targetMarker.setPosition(targets[index]->getPosition());
	targetMarker.move(
			targets[index]->getSize().x / 2.f - targetMarker.getSize() / 2,
			-targetMarker.getSize() * 0.8f);
}

void BattleState::updateCharacters(const float& dt)
{
	for (auto &enemy : enemies)
	{
		enemy->update(dt);
	}

	for (auto &hero : party)
	{
		hero->update(dt);
	}
}

void BattleState::updateActionMenu(const std::string& entry)
{
	if (entry == "Magic")
	{
		initActionMenu(MagicMenu);
	}
	else if (entry == "Object")
	{
		initActionMenu(ObjectMenu);
	}
}

void BattleState::updateActiveMarker()
{
	activeMarker.setPosition(active->getPosition());
	activeMarker.move(
			active->getSize().x / 2.f - activeMarker.getSize() / 2,
			-activeMarker.getSize() * 0.8f);
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

	if (phase != Begin)
	{
		actionMenu->render(renderTexture);
		activeMarker.render(renderTexture);
	}

	if ((phase == TargetSelection || phase == Results) && !triedToFlee)
	{
		targetMarker.render(renderTexture);
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
	std::vector<std::shared_ptr<Character>> renderList;

	renderList.insert(renderList.end(), party.begin(), party.end());
	renderList.insert(renderList.end(), enemies.begin(), enemies.end());

	std::sort(renderList.begin(), renderList.end(), comparePositions);

	for (auto& character : renderList)
	{
		character->render(target);
	}

	/*
	for (auto &enemy : enemies)
	{
		enemy->render(target);
	}

	for (auto &hero : party)
	{
		hero->render(target);
	}
	*/
}

void BattleState::quitToMenu()
{
	endState();
}

// Internal
void BattleState::changePhase(Phase phase)
{
	switch (phase)
	{

	case Begin:

		initActionMenu(Empty);
		break;

	case ActionSelection:

		triedToFlee = false;

		if (this->phase == Begin)
		{
			active = activeQueue[0];
			active->setState(Character::Ready);
		}
		else
		{
			selectNextActive();
		}

		updateActiveMarker();

		if (active->hasStrategy())
		{
			initActionMenu(Empty);
		}
		else
		{
			initActionMenu(MainActions);
		}
		break;

	case TargetSelection:

		// TODO: put in a separate function
		targets.clear();

		if (action->isFriendly())
		{
			targets.insert(targets.end(), party.begin(), party.end());
			targets.insert(targets.end(), enemies.begin(), enemies.end());
		}
		else
		{
			targets.insert(targets.end(), enemies.begin(), enemies.end());
			targets.insert(targets.end(), party.begin(), party.end());
		}

		for (auto character = targets.begin(); character < targets.end();)
		{
			if ((*character)->getHealth() < 0)
			{
				targets.erase(character);
			}
			else
			{
				character++;
			}
		}

		if (active->hasStrategy())
		{
			initActionMenu(Empty);
		}
		else
		{
			initActionMenu(TargetMenu);
		}

		targetMarker.setPosition(targets[0]->getPosition());
		targetMarker.move(
				targets[0]->getSize().x / 2.f - targetMarker.getSize() / 2,
				-targetMarker.getSize() * 0.8f);
		break;

	case Results:

		if (!triedToFlee)
		{
			results = active->use(action, target);

			if (getAliveOnesFrom(party).empty())
			{
				outcome = Lost;
			}
			else if (getAliveOnesFrom(enemies).empty())
			{
				outcome = Won;
			}
		}
		else if (active->flee())
		{
			outcome = Fled;
		}
		break;

	case End:

		if (outcome == Won)
		{
			for (auto& hero : party)
			{
				if (hero->isAlive())
				{
					hero->setState(Character::Victorious);
				}
			}
		}

		break;
	}

	this->phase = phase;
	initDialogueMenu();
}

std::vector<std::shared_ptr<Character> > BattleState::getAliveOnesFrom(
		std::vector<std::shared_ptr<Character>>& characters)
{
	std::vector<std::shared_ptr<Character>> aliveCharacters;

	for (auto character : characters)
	{
		if (character->isAlive())
		{
			aliveCharacters.push_back(character);
		}
	}

	return aliveCharacters;
}

void BattleState::selectNextActive()
{
	for (auto character = activeQueue.begin(); character < activeQueue.end();
			character++)
	{
		if ((*character)->getHealth() < 0)
		{
			activeQueue.erase(character);

			if (character - activeQueue.begin() <=
					static_cast<int>(activeIndex))
			{
				if (activeIndex > 0)
				{
					activeIndex--;
				}
				else
				{
					activeIndex = activeQueue.size() - 1;
				}
			}
		}
	}

	activeIndex = (activeIndex + 1) % activeQueue.size();

	active = activeQueue[activeIndex];
	active->setState(Character::Ready);
}

std::string BattleState::computeOutcome()
{
	std::stringstream stringStream;
	Randomizer& rand = Randomizer::getInstance();

	if (results->getTarget().dHealth < 0
		|| results->getTarget().dMana < 0
		|| results->getTarget().dStamina < 0)
	{
		stringStream << target->getName() << " feels better!";
	}
	else if (results->getTarget().dHealth > 0)
	{
		float aleatory = rand.getBetween(0, 3);
		if (aleatory < 1.f)
		{
			stringStream << "Hard hit!!";
		}
		else if (aleatory < 2.f)
		{
			stringStream << "Bullseye!";
		}
		else
		{
			stringStream << "It's super efficient!";
		}
	}
	else
	{
		stringStream << "Nothing happened.";
	}

	return stringStream.str();
}

// Initialization
void BattleState::initVariables()
{
	phase = BattleState::Begin;
	outcome = None;

	activeIndex = 0;
	triedToFlee = false;
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
	for (auto& enemy : enemies)
	{
		enemy->setStrategy(std::move(NaiveStrategy::getInstance()));
	}

	sf::Vector2f leftStart(700.f, 180.f);
	sf::Vector2f leftStep(-80.f, 100.f);

	for (size_t index = 0; index < enemies.size(); index++)
	{
		enemies[index]->setPosition(sf::Vector2f(
				leftStart.x + leftStep.x * index,
				leftStart.y + leftStep.y * (index % 4)));
		enemies[index]->setSize(sf::Vector2f(200, 200));
	}

	sf::Vector2f rightStart(1200, 200);
	sf::Vector2f rightStep(80, 100);

	for (std::size_t index = 0; index < party.size(); index++)
	{
		party[index]->setPosition(sf::Vector2f(
				rightStart.x + rightStep.x * index,
				rightStart.y + rightStep.y * (index % 4) + 20.f));
		party[index]->setSize(sf::Vector2f(160, 160));
	}

}

void BattleState::initActiveQueue()
{
	activeQueue.clear();
	activeQueue.insert(activeQueue.end(), party.begin(), party.end());
	activeQueue.insert(activeQueue.end(), enemies.begin(), enemies.end());

	std::sort(activeQueue.begin(), activeQueue.end(), compareAgility);
}

void BattleState::initDialogueMenu()
{
	std::vector<std::string> dialogue;
	std::stringstream stringStream;

	switch (phase)
	{

	case Begin:
		dialogue = {"Wild foes appeared!", "Battle starts!!!"};
		break;

	case ActionSelection:
			if (actionMenu->getSelectedEntry() == "Attack")
			{
				dialogue = {"Physical attack."};
			}
			else if (actionMenu->getSelectedEntry() == "Magic")
			{
				dialogue = {"Mostly elemental attacks."};
			}
			else if (actionMenu->getSelectedEntry() == "Object")
			{
				dialogue = {"Utility objects, various effects."};
			}
			else if (actionMenu->getSelectedEntry() == "Flee")
			{
				dialogue = {"Try to flee from the battlefield."};
			}
			else
			{
				dialogue = {""}; // = active->getAction(actionMenu->getSelectedEntry())->getDescription();
			}
		break;

	case TargetSelection:
		dialogue = {"Select the target"};
		break;

	case Results:

		if (triedToFlee)
		{
			stringStream
					<< active->getName() << " tries to flee...";
			dialogue.push_back(stringStream.str());

			if (outcome == None)
			{
				stringStream << " but fails.";
				dialogue.push_back(stringStream.str());
			}
		}
		else if (results)
		{
			stringStream
					<< active->getName() << " uses " << action->getName()
					<< " on " << target->getName() << "!";
			dialogue.push_back(stringStream.str());
			dialogue.push_back(computeOutcome());
		}

		break;

	case End:

		switch (outcome)
		{
		case None:
			break;

		case Won:
			dialogue = {"All enemies defeated", "BATTLE WON!"};
			break;

		case Lost:
			dialogue = {"The entire party is down", "GAME OVER"};
			break;

		case Fled:
			stringStream
					<< active->getName() << " successfully fled!";
			dialogue.push_back(stringStream.str());
			break;
		}
		break;

	}

	if (phase == Begin)
	{
		dialogueMenu.reset(new gui::Dialogue(
				{1700, 250},
				{40, 50},
				50,
				dialogue,
				font));
	}
	else
	{
		dialogueMenu.reset(new gui::Dialogue(
				{1000, 250},
				{40, 50},
				50,
				dialogue,
				font));
	}

	dialogueMenu->setPosition(100, 750);
}

void BattleState::initActionMenu(ActionMenu menu)
{
	switch (menu)
	{

	case Empty:

		actionMenu.reset(new gui::Selection(
				sf::Vector2f(1200, 750),
				sf::Vector2f(600, 250),
				sf::Vector2f(40, 50),
				sf::Vector2u(2, 3),
				sf::Vector2u(2, 2),
				45,
				font));
		break;

	case MainActions:

		actionMenu.reset(new gui::Selection(
				sf::Vector2f(1200, 750),
				sf::Vector2f(600, 250),
				sf::Vector2f(60, 45),
				sf::Vector2u(2, 3),
				sf::Vector2u(2, 2),
				60,
				font));

		actionMenu->addEntry("Attack");
		actionMenu->addEntry("Magic");
		actionMenu->addEntry("Object");
		actionMenu->addEntry("Flee");
		break;

	case MagicMenu:

		actionMenu.reset(new gui::Selection(
				sf::Vector2f(1200, 750),
				sf::Vector2f(600, 250),
				sf::Vector2f(30, 60),
				sf::Vector2u(2, 3),
				sf::Vector2u(2, 2),
				40,
				font));

		for (auto& action : active->getActions())
		{
			if (std::dynamic_pointer_cast<Magic>(action))
			{
				//std::string entry = action->getName();
				//std::transform(entry.begin(), entry.end(), entry.begin(), ::toupper);
				actionMenu->addEntry(action->getName());
			}
		}
		break;

	case ObjectMenu:

		actionMenu.reset(new gui::Selection(
				sf::Vector2f(1200, 750),
				sf::Vector2f(600, 250),
				sf::Vector2f(30, 60),
				sf::Vector2u(2, 3),
				sf::Vector2u(2, 2),
				40,
				font));

		for (auto &action : active->getActions())
		{
			if (std::dynamic_pointer_cast<Object>(action))
			{
				//std::string entry = action->getName();
				//std::transform(entry.begin(), entry.end(), entry.begin(), ::toupper);
				actionMenu->addEntry(action->getName());
			}
		}
		break;

	case TargetMenu:

		actionMenu.reset(new gui::Selection(
				sf::Vector2f(1200, 750),
				sf::Vector2f(600, 250),
				sf::Vector2f(60, 40),
				sf::Vector2u(1, 12),
				sf::Vector2u(1, 3),
				40,
				font));

		for (auto &target : targets)
		{
			actionMenu->addEntry(target->getName());
		}
	}

	this->menu = menu;
}

void BattleState::initPauseMenu()
{
	pauseMenu.reset(new gui::PauseMenu(window, font));

	pauseMenu->addButton("QUIT", 800.f, "Quit");
}

bool BattleState::comparePositions(
		std::shared_ptr<Character> first,
		std::shared_ptr<Character> second)
{
	return (first->getPosition().y + first->getSize().y <
					second->getPosition().y + second->getSize().y);
}

bool BattleState::compareAgility(
		std::shared_ptr<Character> first,
		std::shared_ptr<Character> second)
{
	return (first->getAgility() > second->getAgility());
}

void BattleState::initMarkers()
{
	activeMarker.setSize(40);
	activeMarker.setOrigin(sf::Vector2f(0, activeMarker.getSize()));
	activeMarker.setRotation(90);
	activeMarker.setColor(sf::Color(255, 255, 255, 200));

	targetMarker.setSize(40);
	targetMarker.setOrigin(sf::Vector2f(0, targetMarker.getSize()));
	targetMarker.setRotation(90);
	targetMarker.setColor(sf::Color(255, 255, 255, 200));
}
