/*
 * ChestPlate.h
 *
 *  Created on: Jul 20, 2018
 *      Author: Nikostreet11
 */

#ifndef CHESTPLATE_H_
#define CHESTPLATE_H_

#include "Item.h"

#include <string>

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

#endif /* CHESTPLATE_H_ */
