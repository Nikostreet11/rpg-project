/*
 * MenuComposite.cpp
 *
 *  Created on: Nov 4, 2018
 *      Author: nicop
 */

#include "MenuComposite.h"

#include "MenuContainer.h"

MenuComposite::MenuComposite(std::string name) :
		MenuComponent(name),
		active(NO_ACTIVE) {}

MenuComposite::~MenuComposite() {}

void MenuComposite::addChild(MenuComponent* component) {
	component->setParent(this);
	children.push_back(component);

	if (active == NO_ACTIVE) {
		active = 0;
	}
}

bool MenuComposite::removeChild(int index) {
	if (0 <= index && index < (int) children.size()) {
		delete children.at(index);
		children.erase(children.begin() + index);
		// active legality check
		if (active == (int) children.size()) {
			if (active == 0) {
				active = NO_ACTIVE;
			}
			else {
				active--;
			}
		}
		return true;
	}
	else {
		return false;
	}
}

MenuComponent* MenuComposite::getChild(int index) {
	if (0 <= index && index < (int) children.size()) {
		return children.at(index);
	}
	else {
		return nullptr;
	}
}

bool MenuComposite::isRoot() const {
	if (parent == nullptr) {
		return true;
	}
	else {
		return false;
	}
}

void MenuComposite::action(MenuContainer* menu) {
	menu->setCurrent(this);
}

void MenuComposite::confirm(MenuContainer* menu) {
	if (-1 < active && active < (int) children.size()) {
		getChild(active)->action(menu);
	}
}

void MenuComposite::cancel(MenuContainer* menu) {
	if (parent != nullptr) {
		menu->setCurrent(parent);
	}
}

bool MenuComposite::select(int index) {
	if (0 <= index && index < (int) children.size()) {
		active = index;
		return true;
	}
	else {
		return false;
	}
}

bool MenuComposite::selectBackward() {
	return select(active - 1);
}

bool MenuComposite::selectForward() {
	return select(active + 1);
}

void MenuComposite::resetActive() {
	if (children.size() > 0) {
		active = 0;
	}
	else {
		active = NO_ACTIVE;
	}
}

int MenuComposite::getActive() const {
	return active;
}

std::size_t MenuComposite::getSize() const {
	return children.size();
}
