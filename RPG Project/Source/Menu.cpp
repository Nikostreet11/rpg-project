/*
 * Menu.cpp
 *
 *  Created on: Sep 13, 2018
 *      Author: nicop
 */

#include "Menu.h"

#include "NavigationEntry.h"

// debug includes
#include <iostream>

Menu::Menu() :
		entriesList(0),
		activeEntry(-1) {}

Menu::~Menu() {
	for (std::vector<Entry*>::iterator i = entriesList.begin(); i != entriesList.end(); i++) {
		delete *i;
	}
}

void Menu::addEntry(std::string name) {
	Entry* entry = new Entry(name);
	entriesList.push_back(entry);

	activeEntryNullCheck();
}

void Menu::addEntry(std::string name, State* destination) {
	Entry* entry = new NavigationEntry(name, destination);
	entriesList.push_back(entry);

	activeEntryNullCheck();
}

/*void Menu::addEntry(Character& character) {
	Entry* entry = new BattleEntry(character);
	entriesList.push_back(entry);

	activeEntryNullCheck();
}*/

bool Menu::removeEntry(int position) {
	if (isOutOfBounds(position)) {
		return false;
	}
	else {
		if (activeEntry == position) {
			if (entriesList.size() == 1) {
				activeEntry = NO_ENTRY;
			}
			else {
				activeEntry = 0;
			}
		}
		else if (activeEntry > position) {
			activeEntry--;
		}
		delete entriesList.at(position);
		entriesList.erase(entriesList.begin() + position);
	}
	return true;
}

bool Menu::swapEntries(int firstPos, int secondPos) {
	if (isOutOfBounds(firstPos) || isOutOfBounds(secondPos)) {
		return false;
	}
	else {
		Entry* temp = entriesList.at(firstPos);
		entriesList.at(firstPos) = entriesList.at(secondPos);
		entriesList.at(secondPos) = temp;

		// uncomment to make activeEntry swap with the entry
		/*
		if (activeEntry == firstPos) {
			activeEntry = secondPos;
		}
		else if (activeEntry == secondPos) {
			activeEntry = firstPos;
		}*/
		return true;
	}
}

bool Menu::shiftBackwardEntry(int position) {
	return swapEntries(position, position - 1);
}

bool Menu::shiftForwardEntry(int position) {
	return swapEntries(position, position + 1);
}

bool Menu::setActiveEntry(int position) {
	if (isOutOfBounds(position)) {
		return false;
	}
	else {
		this->activeEntry = position;
		return true;
	}
}

bool Menu::shiftBackwardActive() {
	return setActiveEntry(activeEntry - 1);
}

bool Menu::shiftForwardActive() {
	return setActiveEntry(activeEntry + 1);
}

std::string Menu::getEntryName(int position) {
	if (isOutOfBounds(position)) {
		return "<<NO ENTRY>>";
	}
	else {
		return entriesList.at(position)->getName();
	}
}

int Menu::getLenght() {
	return entriesList.size();
}

bool Menu::isOutOfBounds(int position) {
	if (position < 0 || (unsigned int) position >= entriesList.size()) {
		return true;
	}
	else {
		return false;
	}
}

int Menu::getActiveEntry() const {
	return activeEntry;
}

void Menu::activeEntryNullCheck() {
	if (activeEntry == NO_ENTRY) {
		activeEntry = 0;
	}
}

