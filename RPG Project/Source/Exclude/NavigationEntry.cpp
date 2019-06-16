/*
 * NavigationEntry.cpp
 *
 *  Created on: Oct 3, 2018
 *      Author: nicop
 */

#include "Exclude/NavigationEntry.h"

#include "Game.hpp"

NavigationEntry::NavigationEntry(std::string name, State* destination) :
		Entry(name),
		destination(destination) {}

NavigationEntry::~NavigationEntry() {}

void NavigationEntry::action(Game& game) {
	//game.changeState(destination);
}

