/*
 * MenuContainer.cpp
 *
 *  Created on: Nov 4, 2018
 *      Author: nicop
 */

#include "MenuContainer.h"

MenuContainer::MenuContainer() : root(new MenuComposite("root")), current(root) {}

MenuContainer::~MenuContainer() {
	delete root;
}

void MenuContainer::addChild(MenuComponent* menuComponent) {
	current->addChild(menuComponent);
}

void MenuContainer::confirm() {
	current->confirm(this);
}

void MenuContainer::cancel() {
	current->cancel(this);
}

bool MenuContainer::select(int index) {
	return current->select(index);
}

bool MenuContainer::selectBackward() {
	return current->selectBackward();
}

bool MenuContainer::selectForward() {
	return current->selectForward();
}

void MenuContainer::resetActive() {
	current->resetActive();
}

void MenuContainer::returnToRoot() {
	while (current->getParent() != nullptr) {
		current->cancel(this);
	}
}

const MenuComponent& MenuContainer::getComponent(int index) const {
	return *(current->getChild(index));
}

int MenuContainer::getActive() {
	return current->getActive();
}

void MenuContainer::setCurrent(MenuComposite* current) {
	this->current = current;
}

MenuComposite& MenuContainer::getCurrent() const {
	return *current;
}

std::size_t MenuContainer::getSize() const {
	return current->getSize();
}
