/*
 * Character.h
 *
 *  Created on: Jul 12, 2018
 *      Author: Nikostreet11
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <string>
#include "directionsEnum.h"

class Character {
public:
	explicit Character(std::string name, int level = 1, int posX = -1, int posY = -1);
	virtual ~Character();

	bool move(Direction direction);
	virtual float attack(Character& target);
	int getAgility() const;
	int getEndurance() const;
	float getHealth() const;
	void setHealth(float health);
	int getPosX() const;
	int getPosY() const;
	const std::string& getName() const;

protected:
	void updateStatistics();

	// CHARACTER DATA
	std::string name;
	int level;
	int posX;
	int posY;
	// MAX STATISTICS
	float maxHealth;
	float maxMana;
	float maxStamina;
	// CURRENT STATISTICS
	float health;
	float mana;
	float stamina;
	// SPECIAL STATISTICS
	int strenght;
	int perception;
	int endurance;
	int charm;
	int intelligence;
	int agility;
	int luck;

	const int NO_POSITION = -1;
};

#endif /* CHARACTER_H_ */
