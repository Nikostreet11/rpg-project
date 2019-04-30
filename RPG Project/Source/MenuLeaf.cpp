/*
 * MenuLeaf.cpp
 *
 *  Created on: Nov 6, 2018
 *      Author: nicop
 */

#include "MenuLeaf.h"

#include "MenuContainer.h"

MenuLeaf::MenuLeaf(std::string name) :
		MenuComponent(name) {}

MenuLeaf::~MenuLeaf() {}

void MenuLeaf::action(MenuContainer* menu) {}

