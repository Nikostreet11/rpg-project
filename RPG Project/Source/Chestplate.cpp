/*
 * ChestPlate.cpp
 *
 *  Created on: Jul 20, 2018
 *      Author: Nikostreet11
 */

#include "Chestplate.h"

Chestplate::Chestplate(std::string n, float w=0, int lvl=1) : Item(n, w), level(lvl) {
	armor = level;
}

Chestplate::~Chestplate() {}

