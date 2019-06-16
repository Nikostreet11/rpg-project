/*
 * NavigationEntry.h
 *
 *  Created on: Oct 3, 2018
 *      Author: nicop
 */

#ifndef SOURCE_NAVIGATIONENTRY_H_
#define SOURCE_NAVIGATIONENTRY_H_

#include <string>
#include "Exclude/Entry.h"

class Game; // forward declaration

class NavigationEntry: public Entry {
public:
	NavigationEntry(std::string name, State* destination);
	virtual ~NavigationEntry();

	virtual void action(Game& game) override;

private:
	State* destination;
};

#endif /* SOURCE_NAVIGATIONENTRY_H_ */
