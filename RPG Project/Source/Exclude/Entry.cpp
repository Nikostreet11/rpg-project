/*
 * Entry.cpp
 *
 *  Created on: Sep 19, 2018
 *      Author: nicop
 */

#include "Exclude/Entry.h"

Entry::Entry(std::string name) : name(name) {}

Entry::Entry(const Entry& copy) : name(copy.getName()) {}

Entry::~Entry() {}

Entry& Entry::operator=(const Entry& entry) {
	if (this != &entry) {
		name = entry.getName();
	}
	return *this;
}

void Entry::action(Game& game) {}

const std::string& Entry::getName() const {
	return name;
}

void Entry::setName(const std::string& name) {
	this->name = name;
}
