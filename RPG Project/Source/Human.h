/*
 * Human.h
 *
 *  Created on: Jul 18, 2018
 *      Author: Nikostreet11
 */

#ifndef HUMAN_H_
#define HUMAN_H_

#include "Weapon.h"
#include "Chestplate.h"
#include "Character.h"

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

#endif /* HUMAN_H_ */
