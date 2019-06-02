/*
 * Human.h
 *
 *  Created on: Jul 18, 2018
 *      Author: Nikostreet11
 */

#ifndef EXCLUDE_HUMAN_H_
#define EXCLUDE_HUMAN_H_

#include "Exclude/Character.h"
#include "Exclude/Chestplate.h"
#include "Exclude/Weapon.h"

class Human: public Character {
public:
	explicit Human(std::string name, int level = 1, int posX = -1, int posY = -1);
	virtual ~Human();

	virtual float attack(Character& target);
	const Chestplate* getChestplate() const;
	void setChestplate(Chestplate* chestplate);
	const Weapon* getWeapon() const;
	void setWeapon(Weapon* weapon);

protected:
	Weapon* weapon;
	/*Helmet head;
	Gauntlets arms;*/
	Chestplate* chestplate;
	/*Greaves legs;
	Boots feet;*/
};

#endif /* EXCLUDE_HUMAN_H_ */
