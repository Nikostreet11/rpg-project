/*
 * Node.cpp
 *
 *  Created on: Mar 20, 2019
 *      Author: nicop
 */

#include "Node.hpp"

#include <iostream>

Node::Node() :
children(0) {}

Node::~Node() {
	for (auto iterator = children.begin(); iterator < children.end(); iterator++)
		delete *iterator;
}

bool Node::addChild(Node& node) {
	children.push_back(&node);
	return true;
}
bool Node::removeChild() {
	if (children.size() > 0) {
		children.pop_back();
		return true;
	}
	else
		return false;
}

void Node::draw(sf::RenderTarget& target, sf::RenderStates parentStates) const {
	sf::RenderStates states;
	states.transform = parentStates.transform * this->getTransform();
	onDraw(target, states);
	for (auto iterator = children.begin(); iterator < children.end(); iterator++)
		(*iterator)->draw(target, states);
}
