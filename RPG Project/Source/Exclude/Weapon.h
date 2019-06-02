/*
 * Weapon.h
 *
 *  Created on: Jul 20, 2018
 *      Author: Nikostreet11
 */

#ifndef EXCLUDE_WEAPON_H_
#define EXCLUDE_WEAPON_H_

#include <string>
#include "Exclude/Item.h"

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

#endif /* EXCLUDE_WEAPON_H_ */
