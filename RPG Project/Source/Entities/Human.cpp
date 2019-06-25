/*
 * Human.cpp
 *
 *  Created on: Jul 18, 2018
 *      Author: Nikostreet11
 */

#include "Human.hpp"

Human::Human(
		Type type,
		const sf::Texture& spriteset,
		sf::Vector2f position,
		sf::Vector2f size) :
		Character()
{
	this->type = type;

	initVariables();
	initSprite(spriteset, position, size);
	/*
	weapon = nullptr;
	chestplate = nullptr;
	*/
}

Human::~Human()
{
}

/*
float Human::attack(Character& target)
{
	Randomizer& randomizer = Randomizer::getInstance();
	float damage;
	float accuracy = 50 + agility - target.getAgility();
	if (randomizer.percentageOn(accuracy)) {
		// strike
		damage = strenght - target.getEndurance() * 0.5;
		if (weapon != nullptr) {
			// weapon damage
			damage += weapon->getImpact();
		}
		float criticalChance = 10 + perception;
		if (randomizer.percentageOn(criticalChance)) {
			// critical damage
			damage *= 1.5;
		}
		Human* human = dynamic_cast<Human*>(&target);
		if (human) {
			// target armor
			if (human->chestplate != nullptr) {
				damage -= human->chestplate->getArmor() * 0.5;
			}
		}
		if (damage < 0) {
			// block
			damage = 0;
		}
		target.setHealth(target.getHealth() - damage);
	}
	else {
		// miss
		damage = 0;
	}
	return damage;
}
*/

/*
const Chestplate* Human::getChestplate() const {
	return chestplate;
}

void Human::setChestplate(Chestplate* chestplate) {
	this->chestplate = chestplate;
}

const Weapon* Human::getWeapon() const {
	return weapon;
}

void Human::setWeapon(Weapon* weapon) {
	this->weapon = weapon;
}
*/

// Initialization
void Human::initVariables()
{
	spriteOffset = {16, 16};
	spriteSize = {48, 48};
	spriteSpacing = {16, 16};
	spriteIndex = {1, 0};
}
