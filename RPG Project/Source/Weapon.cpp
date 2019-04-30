/*
 * Weapon.cpp
 *
 *  Created on: Jul 20, 2018
 *      Author: Nikostreet11
 */

#include "Weapon.h"

Weapon::Weapon(std::string n, float w=0, int lvl=1) : Item(n, w), level(lvl) {
	impact = level * 2;
}

Weapon::~Weapon() {}

