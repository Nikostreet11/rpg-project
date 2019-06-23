/*
 * Dialogue.cpp
 *
 *  Created on: Mar 25, 2019
 *      Author: nicop
 */

#include "Dialogue.hpp"

namespace gui
{

Dialogue::Dialogue(
		//sf::Vector2f position,
		sf::Vector2f size,
		sf::Vector2f offset,
		unsigned textSize,
		std::vector<std::string> dialogue,
		std::shared_ptr<sf::Font> font)
{
	//this->position = position;
	this->size = size;
	this->offset = offset;
	this->textSize = textSize;
	this->dialogue = dialogue;
	this->font = std::move(font);

	initVariables();
	initContainer();
	initCurrentLine();
	/*
	text.setFont(font);
	text.setCharacterSize(characterSize);
	text.setFillColor(sf::Color::White);
	text.setString(string);
	*/
}

Dialogue::~Dialogue()
{
}

void Dialogue::update()
{
}

void Dialogue::render(sf::RenderTarget& target)
{
	sf::RenderStates states;
	states.transform *= this->getTransform();
	target.draw(container, states);
	target.draw(currentLine, states);
}

void Dialogue::setNextLine()
{
	lineIndex++;

	if (lineIndex < dialogue.size())
	{
		currentLine.setString(dialogue[lineIndex]);
	}
}

/*
const std::string& Dialogue::getCurrentLine() const
{
	return currentLine.getString();
}
*/

bool Dialogue::isEnded() const
{
	if (lineIndex < dialogue.size())
	{
		return false;
	}
	else
	{
		return true;
	}
}

/*
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
*/

void Dialogue::initVariables()
{
	lineIndex = 0;
}

void Dialogue::initContainer()
{
	container.setFillColor(sf::Color::Blue);
	container.setOutlineThickness(-3.f);
	container.setOutlineColor(sf::Color::White);
	container.setSize(size);
}

void Dialogue::initCurrentLine()
{
	currentLine.setPosition(offset);
	currentLine.setFont(*font);
	currentLine.setCharacterSize(textSize);
	currentLine.setFillColor(sf::Color::White);
	currentLine.setString(dialogue[lineIndex]);
}

} /* namespace gui */
