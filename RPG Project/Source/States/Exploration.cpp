/*
 * Exploration.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: nicop
 */

#include "Exploration.h"

#include "../DebugMap.h"
#include "../ServiceLocator.h"
#include "../directionsEnum.h"

#include <iostream>
#include <vector>

#include "../Game.hpp"
#include "../States/Battle.h"

//Exploration* Exploration::instance = nullptr;

Exploration::Exploration(
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<std::map<std::string, int>> supportedKeys,
		std::shared_ptr<std::stack<std::unique_ptr<State>>> states) :
State(window, supportedKeys, states),
map(new DebugMap(100, 100)) {}

Exploration::~Exploration() {/*
	instance = nullptr;

	delete map;
	map = nullptr;
*/}

void Exploration::endState()
{
}

void Exploration::update(const float& dt)
{
}

void Exploration::render(std::shared_ptr<sf::RenderTarget> target)
{
}

/*Exploration* Exploration::getInstance() {
	if (instance == nullptr) {
		instance = new Exploration();
	}
	return instance;
}*/

void Exploration::draw() {
	GraphicService* graphicService = ServiceLocator::getGraphicService();
	graphicService->drawExploration(*this);
}

void Exploration::keyPressed_W(Game& game) {
	moveParty(Direction::up, game);
	/*if (!party.isEmpty()) {
		int newX = party.getHero(0)->getPosX();
		int newY = party.getHero(0)->getPosY() - 1;
		if (!map->isOutOfBounds(newX, newY) && map->at(newX, newY).isCrossable()) {
			party.move(up);
			// TODO: movement animation
			}
		}
	}*/
}

void Exploration::keyPressed_A(Game& game) {
	moveParty(Direction::left, game);
	/*if (!party.isEmpty()) {
		int posX = party.getHero(0)->getPosX() - 1;
		int posY = party.getHero(0)->getPosY();
		if (!map->isOutOfBounds(posX, posY) && map->at(posX, posY).isCrossable()) {
			party.move(left);
			// TODO: movement animation
		}
	}*/
}

void Exploration::keyPressed_S(Game& game) {
	moveParty(Direction::down, game);
	/*if (!party.isEmpty()) {
		int posX = party.getHero(0)->getPosX();
		int posY = party.getHero(0)->getPosY() + 1;
		if (!map->isOutOfBounds(posX, posY) && map->at(posX, posY).isCrossable()) {
			party.move(down);
			// TODO: movement animation
		}
	}*/
}

void Exploration::keyPressed_D(Game& game) {
	moveParty(Direction::right, game);
	/*if (!party.isEmpty()) {
		int posX = party.getHero(0)->getPosX() + 1;
		int posY = party.getHero(0)->getPosY();
		if (!map->isOutOfBounds(posX, posY) && map->at(posX, posY).isCrossable()) {
			party.move(right);
			// TODO: movement animation
		}
	}*/
}

void Exploration::keyPressed_Enter(Game& game) {}

const TileMap& Exploration::getMap() const {
	return *map;
}

const Party& Exploration::getParty() const {
	return party;
}

// Initialization functions
void Exploration::initKeybinds()
{
}

void Exploration::moveParty(Direction direction, Game& game) {
	if (!party.isEmpty()) {
		int newX = party.getHero(0)->getPosX();
		int newY = party.getHero(0)->getPosY();

		switch (direction) {
		case Direction::up:
			newY -= 1;
			break;
		case Direction::left:
			newX -= 1;
			break;
		case Direction::down:
			newY += 1;
			break;
		case Direction::right:
			newX += 1;
			break;
		case Direction::none:
			break;
		}

		/*
		if (!map->isOutOfBounds(newX, newY) && map->at(newX, newY).isCrossable()) {
			party.move(direction);
			// TODO: movement animation
			if (map->getTile(newX, newY).isDangerous()) {
				Randomizer& randomizer = Randomizer::getInstance();
				if (randomizer.percentageOn(100)) {
					// starts battle
					Battle* battle = Battle::getInstance();
					std::vector<Character*> partyVector;
					for (int count = 0; count < party.getSize(); count++) {
						partyVector.push_back(party.getHero(count));
					}
					battle->setParty(partyVector);
					battle->setFoes(map->getFoes(party)); // factory method
					battle->setBackground(map->getBackground());
					//game.changeState(battle);
				}
			}
		}
		*/
	}
}

