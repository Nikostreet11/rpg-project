/*
 * InnerWindow.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: nicop
 */

#include "InnerWindow.hpp"

InnerWindow::InnerWindow(sf::Vector2f size) {
	rectangle.setSize(size);
	rectangle.setFillColor(sf::Color::Blue);
	rectangle.setOutlineThickness(-7);
	rectangle.setOutlineColor(sf::Color::White);
}

InnerWindow::~InnerWindow() {}

void InnerWindow::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(rectangle, states);
}

void InnerWindow::setSize(sf::Vector2f size) {
	rectangle.setSize(size);
}

const sf::Vector2f& InnerWindow::getSize() const {
	return rectangle.getSize();
}
