/*
 * Battle.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: nicop
 */

#include "Battle.h"

#include <iostream>
#include "../Exclude/GraphicEngine.h"
#include "../Exclude/Graphics/Dialogue.hpp"
#include "../Exclude/MenuComposite.h"
#include "../Exclude/MenuLeaf.h"
#include "../Exclude/ServiceLocator.h"

//Battle* Battle::instance = nullptr;

Battle::Battle(
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<std::map<std::string, int>> supportedKeys,
		std::shared_ptr<std::stack<std::unique_ptr<State>>> states) :
State(window, supportedKeys, states)/*,
		state(SubState::player_select_action),
		background(Background::none),
		party(0),
		foes(0) */{

	/*loadMenu();
	loadGraphics();*/
}

Battle::~Battle() {
	//instance = nullptr;
}

void Battle::endState()
{
}

void Battle::update(const float& dt)
{
}

void Battle::render(std::shared_ptr<sf::RenderTarget> target)
{
}

/*Battle* Battle::getInstance() {
	if (instance == nullptr) {
		instance = new Battle();
	}
	return instance;
}*/

/*void Battle::draw() {
	// TODO: rework GraphicEngine getter system
	GraphicService* graphicService = ServiceLocator::getGraphicService();
	//graphicService->drawBattle(*this);
	GraphicEngine& graphicEngine = dynamic_cast<GraphicEngine&>(*graphicService);

	switch (state) {
	case Battle::SubState::start:
		draw_start(graphicEngine);
		break;
	case Battle::SubState::player_select_action:
		draw_player_select_action(graphicEngine);
		break;
	}
}

void Battle::draw_start(GraphicEngine& graphicEngine) {
	// get the window to draw on
	sf::RenderWindow& window = graphicEngine.getWindow();

	// draw battle background
	sf::Sprite& backgroundSprite = graphicEngine.getSprite(background);
	backgroundSprite.setPosition(sf::Vector2f(
			 window.getSize().x * 0,
			 window.getSize().y * 0));
	backgroundSprite.setScale(sf::Vector2f(
			(float) window.getSize().x / backgroundSprite.getTextureRect().width,
			(float) window.getSize().y / backgroundSprite.getTextureRect().height
			));
	window.draw(backgroundSprite);

	// create dialogue window
	InnerWindow dialogueWindow;
	dialogueWindow.setSize(sf::Vector2f(
			graphicEngine.getWindow().getSize().x,
			graphicEngine.getWindow().getSize().y * 0.25
			));

	// create dialogue
	Dialogue dialogue;
	dialogue.setCharacterSize(30);
	dialogue.setString("Some wild enemies appeared!");
	dialogue.setPosition(sf::Vector2f(30, 30));

	// attach dialogue to the window
	dialogueWindow.addChild(dialogue);

	// draw the dialogue window on screen
	dialogueWindow.setPosition(sf::Vector2f(
			0,
			graphicEngine.getWindow().getSize().y * 0.75
			));
	window.draw(dialogueWindow);

	// draw battle characters
	sf::Vector2f start(window.getSize().x * 0.7, window.getSize().y * 0.25);
	sf::Vector2f step(window.getSize().x * 0.0275, window.getSize().y * 0.1);

	for (int index = 0; index < (int) party.size(); index++) {
		sf::Sprite& sprite = graphicEngine.getSprite(*(party.at(index)));
		sprite.setPosition(sf::Vector2f(
				start.x + index * step.x,
				start.y + index * step.y));
		sprite.setScale(sf::Vector2f(
				(float) 64 / sprite.getTextureRect().width,
				(float) 64 / sprite.getTextureRect().height));
		window.draw(sprite);
	}

	for (int index = 0; index < (int) foes.size(); index++) {
		sf::Sprite& sprite = graphicEngine.getSprite(*(foes.at(index)));
		sprite.setPosition(sf::Vector2f(
				window.getSize().x - start.x - index * step.x,
				start.y + (index % 4) * step.y));
		sprite.setScale(sf::Vector2f(
				(float) 64 / sprite.getTextureRect().width,
				(float) 64 / sprite.getTextureRect().height));
		window.draw(sprite);
	}
}

void Battle::draw_player_select_action(GraphicEngine& graphicEngine) {
	// get the window to draw on
	sf::RenderWindow& window = graphicEngine.getWindow();

	// draw battle background
	sf::Sprite& backgroundSprite = graphicEngine.getSprite(background);
	backgroundSprite.setPosition(sf::Vector2f(
			 window.getSize().x * 0,
			 window.getSize().y * 0));
	backgroundSprite.setScale(sf::Vector2f(
			(float) window.getSize().x / backgroundSprite.getTextureRect().width,
			(float) window.getSize().y / backgroundSprite.getTextureRect().height
			));
	window.draw(backgroundSprite);

	// create dialogue window
	InnerWindow dialogueWindow;
	dialogueWindow.setSize(sf::Vector2f(
			graphicEngine.getWindow().getSize().x * 0.6,
			graphicEngine.getWindow().getSize().y * 0.25
			));

	// create dialogue
	Dialogue dialogue;
	dialogue.setCharacterSize(30);
	dialogue.setString("menu.getActive().getDescription()");
	dialogue.setPosition(sf::Vector2f(30, 30));

	// attach dialogue to the window
	dialogueWindow.addChild(dialogue);

	// draw the dialogue window on screen
	dialogueWindow.setPosition(sf::Vector2f(
			0,
			graphicEngine.getWindow().getSize().y * 0.75));
	window.draw(dialogueWindow);

	// draw the command window on screen

	window.draw(commandWindow);

	// draw battle characters
	sf::Vector2f start(window.getSize().x * 0.7, window.getSize().y * 0.25);
	sf::Vector2f step(window.getSize().x * 0.0275, window.getSize().y * 0.1);

	// draw party
	for (int index = 0; index < (int) party.size(); index++) {
		sf::Sprite& sprite = graphicEngine.getSprite(*(party.at(index)));
		sprite.setPosition(sf::Vector2f(
				start.x + index * step.x,
				start.y + index * step.y));
		sprite.setScale(sf::Vector2f(
				(float) 64 / sprite.getTextureRect().width,
				(float) 64 / sprite.getTextureRect().height));
		window.draw(sprite);
	}

	// draw foes
	for (int index = 0; index < (int) foes.size(); index++) {
		sf::Sprite& sprite = graphicEngine.getSprite(*(foes.at(index)));
		sprite.setPosition(sf::Vector2f(
				window.getSize().x - start.x - index * step.x,
				start.y + (index % 4) * step.y));
		sprite.setScale(sf::Vector2f(
				(float) 64 / sprite.getTextureRect().width,
				(float) 64 / sprite.getTextureRect().height));
		window.draw(sprite);
	}
}

void Battle::keyPressed_W(Game& game) {
	switch (state) {
	case Battle::SubState::start:
		break;
	case Battle::SubState::player_select_action:
		commands.moveMarkerIndex(Direction::up);
		break;
	}
}

void Battle::keyPressed_A(Game& game) {
	switch (state) {
	case Battle::SubState::start:
		break;
	case Battle::SubState::player_select_action:
		commands.moveMarkerIndex(Direction::left);
		break;
	}
}

void Battle::keyPressed_S(Game& game) {
	switch (state) {
	case Battle::SubState::start:
		break;
	case Battle::SubState::player_select_action:
		commands.moveMarkerIndex(Direction::down);
		break;
	}
}

void Battle::keyPressed_D(Game& game) {
	switch (state) {
	case Battle::SubState::start:
		break;
	case Battle::SubState::player_select_action:
		commands.moveMarkerIndex(Direction::right);
		break;
	}
}

void Battle::keyPressed_Enter(Game& game) {}

void Battle::setParty(std::vector<Character*> party) {
	this->party = party;
}

void Battle::setFoes(std::vector<Foe*> foes) {
	this->foes = foes;
}

Battle::Background Battle::getBackground() const {
	return background;
}

void Battle::setBackground(Battle::Background background) {
	this->background = background;
}

const std::vector<Foe*>& Battle::getFoes() const {
	return foes;
}

const std::vector<Character*>& Battle::getParty() const {
	return party;
}

const MenuContainer& Battle::getMenu() const {
	return menu;
}

Battle::SubState Battle::getState() const {
	return state;
}

void Battle::setState(Battle::SubState state) {
	this->state = state;
}*/

// Initialization functions
void Battle::initKeybinds()
{
}

/*void Battle::loadMenu() {
	menu.addChild(new MenuComposite("Dummy"));
	menu.addChild(new MenuComposite("Dummy"));
	menu.addChild(new MenuComposite("Dummy"));
	menu.addChild(new MenuComposite("Dummy"));
	menu.addChild(new MenuComposite("Dummy"));

	menu.addChild(new MenuLeaf("Attack")); // active
	menu.addChild(new MenuComposite("Magic"));

	menu.addChild(new MenuComposite("Dummy"));
	menu.addChild(new MenuComposite("Dummy"));

	menu.addChild(new MenuComposite("Ability"));
	menu.addChild(new MenuComposite("Object"));

	menu.addChild(new MenuComposite("Dummy"));
	menu.addChild(new MenuComposite("Dummy"));
	menu.addChild(new MenuComposite("Dummy"));
	menu.addChild(new MenuComposite("Dummy"));
	//menu.addChild(new MenuComposite("Dummy"));

	menu.selectForward();
	menu.confirm();

	// Magic sub-menu
	menu.addChild(new MenuLeaf("Fire")); // active
	menu.addChild(new MenuLeaf("Blizzard"));
	menu.addChild(new MenuLeaf("Thunder"));

	menu.cancel();
	menu.selectForward();
	menu.confirm();

	// Ability sub-menu
	menu.addChild(new MenuLeaf("Heal")); // active
	menu.addChild(new MenuLeaf("Courage"));
	menu.addChild(new MenuLeaf("Flee"));

	menu.cancel();
	menu.selectForward();
	menu.confirm();

	// Object sub-menu
	menu.addChild(new MenuLeaf("Potion")); // active
	menu.addChild(new MenuLeaf("Ether"));
	menu.addChild(new MenuLeaf("Phoenix down"));

	menu.cancel();
	menu.resetActive();
}

void Battle::loadGraphics() {
	// TODO: rework GraphicEngine getter system
	GraphicService* graphicService = ServiceLocator::getGraphicService();
	//graphicService->drawBattle(*this);
	GraphicEngine& graphicEngine = dynamic_cast<GraphicEngine&>(*graphicService);

	// initialize command window
	commandWindow.setSize(sf::Vector2f(
			graphicEngine.getWindow().getSize().x * 0.4,
			graphicEngine.getWindow().getSize().y * 0.25));

	// initialize selection
	commands.setSize(sf::Vector2f(
			commandWindow.getSize().x - 14,
			commandWindow.getSize().y - 14));
	commands.setOffset(sf::Vector2f(50, 25));
	commands.setTextColor(sf::Color::White);
	commands.setMarkerColor(sf::Color::White);
	commands.setScrollsColor(sf::Color::White);

	// attach commands to the window
	commands.setPosition(sf::Vector2f(7, 7));
	commandWindow.addChild(commands);
	commandWindow.setPosition(sf::Vector2f(
			graphicEngine.getWindow().getSize().x * 0.6,
			graphicEngine.getWindow().getSize().y * 0.75));

	// observer method
	std::vector<std::string> menuStrings;
	for (std::size_t index = 0; index < menu.getSize(); index++) {
		menuStrings.push_back(menu.getComponent(index).getName());
	}
	commands.setEntries(menuStrings);
	commands.setFieldSize(sf::Vector2i(4, std::ceil(menuStrings.size() / 4.)));
	commands.setViewSize(sf::Vector2i(2, 2));
	commands.setViewIndex(sf::Vector2i(1, 1));
	commands.setMarkerIndex(sf::Vector2i(0, 0));
}*/
