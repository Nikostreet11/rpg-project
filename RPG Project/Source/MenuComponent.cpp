/*
 * MenuComponent.cpp
 *
 *  Created on: Nov 4, 2018
 *      Author: nicop
 */

#include "MenuComponent.h"

#include "MenuComposite.h"

MenuComponent::MenuComponent(std::string name) :
		parent(nullptr),
		name(name) {}

MenuComponent::~MenuComponent() {}

const std::string& MenuComponent::getName() const {
	return name;
}

void MenuComponent::setName(const std::string& name) {
	this->name = name;
}

MenuComposite* MenuComponent::getParent() const {
	return parent;
}

void MenuComponent::setParent(MenuComposite* parent) {
	this->parent = parent;
}

