/*
 * Weapon.h
 *
 *  Created on: Jul 20, 2018
 *      Author: Nikostreet11
 */

#ifndef WEAPON_H_
#define WEAPON_H_

#include "Item.h"

#include <string>

class Weapon: public Item {
public:
	Weapon(std::string name, float weight, int level);
	virtual ~Weapon();

	int getImpact() const {
		return impact;
	}

protected:
	int level;
	int impact;
};

#endif /* WEAPON_H_ */
