/*
 * Entry.h
 *
 *  Created on: Sep 19, 2018
 *      Author: nicop
 */

#ifndef EXCLUDE_ENTRY_H_
#define EXCLUDE_ENTRY_H_

#include <string>
#include "States/State.hpp"

class Game;

class Entry {
public:
	Entry(std::string name);
	Entry(const Entry& copy);
	virtual ~Entry();

	virtual Entry& operator=(const Entry& entry);
	virtual void action(Game& game);

	// getter and setters
	virtual const std::string& getName() const;
	virtual void setName(const std::string& name);

private:
	std::string name;
};

#endif /* EXCLUDE_ENTRY_H_ */
