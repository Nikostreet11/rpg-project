/*
 * Player.cpp
 *
 *  Created on: Jul 26, 2018
 *      Author: nicop
 */

#include "Exclude/Party.h"

#include <iostream>
#include "Exclude/Human.h"

Party::Party() : heroes(0), lastMovements(0) {
	/*for (int count = 0; count < maxSize; count++) {
		heroes.at(count) = nullptr;
		lastMovements.at(count) = none;
	}*/
	addHero(new Human("Warrior", 1, 0, 0));
	addHero(new Human("Warrior", 1, 0, 0));
	addHero(new Human("Warrior", 1, 0, 0));
	addHero(new Human("Warrior", 1, 0, 0));
	/*heroes.at(0) = new Human("Warrior");
	heroes.at(1) = new Human("Wizard");
	heroes.at(2) = new Human("Cleric");
	heroes.at(3) = new Human("Warmage");*/
}

Party::~Party() {
	for (std::vector<Human*>::iterator i = heroes.begin(); i != heroes.end(); i++) {
		delete *i;
	}
}

/*void Party::moveRight() {
	if (heroes.size() > 0) {
		lastMovements.pop_back();
		lastMovements.push_front(right);
		updateHeroesPosition();
	}
}

void Party::moveLeft() {
	if (heroes.size() > 0) {
		lastMovements.pop_back();
		lastMovements.push_front(left);
		updateHeroesPosition();
	}
}

void Party::moveDown() {
	if (heroes.size() > 0) {
		lastMovements.pop_back();
		lastMovements.push_front(down);
		updateHeroesPosition();
	}
}

void Party::moveUp() {
	if (heroes.size() > 0) {
		lastMovements.pop_back();
		lastMovements.push_front(up);
		updateHeroesPosition();
	}
}*/

void Party::move(Direction direction) {
	if (heroes.size() > 0) {
		lastMovements.pop_back();
		lastMovements.insert(lastMovements.begin(), direction);
		updateHeroesPosition();
	}
}

bool Party::addHero(Human* hero) {
	if (isFull()) {
		delete hero;
		return false;
	}
	else {
		heroes.push_back(hero);
		lastMovements.push_back(Direction::none);
		return true;
	}
}

bool Party::removeHero() {
	if(isEmpty()) {
		return false;
	}
	else {
		heroes.pop_back();
		lastMovements.pop_back();
		return true;
	}
}

/*bool Party::removeHero(int position) {
	if (isOutOfBounds(position)) {
		return false;
	}
	else {
		heroes.erase(heroes.begin() + position);
		lastMovements.erase(lastMovements.begin() + position);
		return true;
	}
}*/

/*Human* Party::getHero() const {
	return heroes.at(0);
}*/

Human* Party::getHero(int position) const {
	if (isOutOfBounds(position)) {
		return nullptr;
	}
	else {
		return heroes.at(position);
	}
}

int Party::getSize() const {
	return heroes.size();
}

bool Party::isEmpty() const {
	if (heroes.size() == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Party::isFull() const {
	if (heroes.size() >= (unsigned int) maxSize) {
		return true;
	}
	else {
		return false;
	}
}


void Party::updateHeroesPosition() {
	for (int position = 0; (unsigned int) position < heroes.size(); position++) {
		Direction direction = lastMovements.at(position);
		getHero(position)->move(direction);
		/*switch (lastMovements.at(position)) {
		case up:
			getHero(position)->move(up);
			break;
		case left:
			getHero(position)->move(left);
			break;
		case down:
			getHero(position)->move(down);
			break;
		case right:
			getHero(position)->move(right);
			break;
		case none:
			break;
		}*/
	}
}

bool Party::isOutOfBounds(int position) const {
	if (position < 0 || (unsigned int) position >= heroes.size()) {
		return true;
	}
	else {
		return false;
	}
}

