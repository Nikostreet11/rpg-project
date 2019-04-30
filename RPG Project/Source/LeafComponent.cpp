/*
 * LeafComponent.cpp
 *
 *  Created on: Nov 1, 2018
 *      Author: Nikostreet11
 */

#include "LeafComponent.h"

LeafComponent::LeafComponent(Component* parent) : Component(parent) {}

LeafComponent::~LeafComponent() {}

void LeafComponent::addChild(Component* component) {/* TODO */}

bool LeafComponent::removeChild(int index) { return false; }

Component* LeafComponent::getChild(int index) { return nullptr; }

