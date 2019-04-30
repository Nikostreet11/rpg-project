/*
 * Composite.cpp
 *
 *  Created on: Nov 1, 2018
 *      Author: Nikostreet11
 */

#include "Composite.h"

Composite::Composite(Component* parent) : Component(parent), children(0) {}

Composite::~Composite() {
	for (auto iterator = children.begin(); iterator != children.end(); iterator++) {
		delete *iterator;
	}
	children.clear();
}

void Composite::addChild(Component* component) {
	component->setParent(this);
	children.push_back(component);
}

bool Composite::removeChild(int index) {
	if (0 <= index && index < (int) children.size()) {
		delete children.at(index);
		children.erase(children.begin() + index);
		return true;
	}
	else {
		return false;
	}
}

Component* Composite::getChild(int index) {
	if (0 <= index && index < (int) children.size()) {
		return children.at(index);
	}
	else {
		return nullptr;
	}
}

