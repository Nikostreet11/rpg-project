/*
 * Monster.cpp
 *
 *  Created on: Jul 20, 2018
 *      Author: Nikostreet11
 */

#include "Exclude/Foe.h"

Foe::Foe(std::string name, int level, Item* loot) :
		Character(name, level), loot(loot) {}

Foe::~Foe() {}

