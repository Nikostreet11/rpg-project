/*
 * Component.cpp
 *
 *  Created on: Nov 1, 2018
 *      Author: Nikostreet11
 */

#include "Exclude/Component.h"

Component::Component(Component* parent) : parent(parent) {}

Component::~Component() {}

void Component::setParent(Component* parent) {
	this->parent = parent;
}

