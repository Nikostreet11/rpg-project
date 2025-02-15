/*
 * Menu.h
 *
 *  Created on: Sep 13, 2018
 *      Author: nicop
 */

#ifndef EXCLUDE_MENU_H_
#define EXCLUDE_MENU_H_

#include <vector>
#include <string>

#include "Exclude/Character.h"
#include "Exclude/Entry.h"
#include "States/State.hpp"

class Menu {
public:
	Menu();
	virtual ~Menu();

	void addEntry(std::string name);
	void addEntry(std::string name, State* destination);
	//void addEntry(Character& character);
	bool removeEntry(int position);
	bool swapEntries(int firstPos, int secondPos);
	bool shiftBackwardEntry(int position);
	bool shiftForwardEntry(int position);

	bool setActiveEntry(int position);
	bool shiftBackwardActive();
	bool shiftForwardActive();

	std::string getEntryName(int position);
	int getLenght();
	int getActiveEntry() const;

protected:
	bool isOutOfBounds(int position);
	void activeEntryNullCheck();

	std::vector<Entry*> entriesList;
	int activeEntry;

	const int NO_ENTRY = -1;
};

#endif /* EXCLUDE_MENU_H_ */
