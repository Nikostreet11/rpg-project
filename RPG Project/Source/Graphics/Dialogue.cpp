/*
 * Dialogue.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: nicop
 */

#include "Dialogue.hpp"

Dialogue::Dialogue(unsigned int characterSize, sf::String string) {
	font.loadFromFile("fonts/arial.ttf");
	text.setFont(font);
	text.setCharacterSize(characterSize);
	text.setFillColor(sf::Color::White);
	text.setString(string);
}

Dialogue::~Dialogue() {}

void Dialogue::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(text, states);
}

unsigned int Dialogue::getCharacterSize() const {
	return text.getCharacterSize();
}

void Dialogue::setCharacterSize(unsigned int size) {
	text.setCharacterSize(size);
}

const sf::String& Dialogue::getString() const {
	return text.getString();
}

void Dialogue::setString(const sf::String& string) {
	text.setString(string);
}
