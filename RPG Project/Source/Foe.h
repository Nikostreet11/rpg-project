/*
 * Monster.h
 *
 *  Created on: Jul 20, 2018
 *      Author: Nikostreet11
 */

#ifndef FOE_H_
#define FOE_H_

#include "Character.h"

#include "Item.h"

//#include <vector>

class Foe: public Character {
public:
	Foe(std::string name, int level = 1, Item* loot = nullptr);
	virtual ~Foe();

private:
	Item* loot;
	// std::vector<Item*> loot;
};

#endif /* FOE_H_ */
