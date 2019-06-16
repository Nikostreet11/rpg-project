/*
 * Character.cpp
 *
 *  Created on: Jul 12, 2018
 *      Author: Nikostreet11
 */

#include "Exclude/Character.h"

#include "Exclude/Human.h"
#include "Exclude/Randomizer.h"

Character::Character(std::string name, int level, int posX, int posY) :
		name(name), level(level),
		posX(posX), posY(posY) {
	updateStatistics();
}

Character::~Character() {}

bool Character::move(Direction direction) {
	if (posX == NO_POSITION || posY == NO_POSITION) {
		return false;
	}
	else {
		switch (direction) {
		case Direction::up:
			posY--;
			break;
		case Direction::left:
			posX--;
			break;
		case Direction::down:
			posY++;
			break;
		case Direction::right:
			posX++;
			break;
		case Direction::none:
			break;
		}
		return true;
	}
}

float Character::attack(Character& target) {
	Randomizer& randomizer = Randomizer::getInstance();
	float damage;
	float accuracy = 50 + agility - target.agility;
	if (randomizer.percentageOn(accuracy)) {
		// strike
		damage = strenght - target.endurance * 0.5;
		float criticalChance = 10 + perception;
		if (randomizer.percentageOn(criticalChance)) {
			// critical damage
			damage *= 1.5;
		}
		Human* human = dynamic_cast<Human*>(&target);
		if (human) {
			// target armor
			if (human->getChestplate() != nullptr) {
				damage -= human->getChestplate()->getArmor() * 0.5;
			}
		}
		if (damage < 0) {
			// block
			damage = 0;
		}
		target.health -= damage;
	}
	else {
		// miss
		damage = 0;
	}
	return damage;
}

int Character::getAgility() const {
	return agility;
}

int Character::getEndurance() const {
	return endurance;
}

float Character::getHealth() const {
	return health;
}

void Character::setHealth(float health) {
	this->health = health;
}

void Character::updateStatistics() {
	maxHealth = level * 10;
	maxMana = level * 10;
	maxStamina = level * 10;

	health = maxHealth;
	mana = maxMana;
	stamina = maxStamina;

	strenght = 1;
	perception = 1;
	endurance = 1;
	charm = 1;
	intelligence = 1;
	agility = 1;
	luck = 1;
}

int Character::getPosX() const {
	return posX;
}

int Character::getPosY() const {
	return posY;
}

const std::string& Character::getName() const {
	return name;
}
