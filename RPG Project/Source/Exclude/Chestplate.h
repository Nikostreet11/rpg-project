/*
 * ChestPlate.h
 *
 *  Created on: Jul 20, 2018
 *      Author: Nikostreet11
 */

#ifndef EXCLUDE_CHESTPLATE_H_
#define EXCLUDE_CHESTPLATE_H_

#include <string>
#include "Exclude/Item.h"

class Chestplate: public Item {
public:
	Chestplate(std::string name, float weight, int level);
	virtual ~Chestplate();

	int getArmor() const {
		return armor;
	}

protected:
	int level;
	int armor;
};

#endif /* EXCLUDE_CHESTPLATE_H_ */
