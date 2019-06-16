/*
 * Monster.h
 *
 *  Created on: Jul 20, 2018
 *      Author: Nikostreet11
 */

#ifndef EXCLUDE_FOE_H_
#define EXCLUDE_FOE_H_

#include "Exclude/Character.h"
#include "Exclude/Item.h"

//#include <vector>

class Foe: public Character {
public:
	Foe(std::string name, int level = 1, Item* loot = nullptr);
	virtual ~Foe();

private:
	Item* loot;
	// std::vector<Item*> loot;
};

#endif /* EXCLUDE_FOE_H_ */
