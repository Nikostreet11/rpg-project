/*
 * Dialogue.hpp
 *
 *  Created on: Mar 25, 2019
 *      Author: nicop
 */

#ifndef GUI_DIALOGUE_HPP_
#define GUI_DIALOGUE_HPP_

#include "pch.hpp"

namespace gui
{

class Dialogue :
		public sf::Transformable
{
public:
	Dialogue(
			//sf::Vector2f position,
			sf::Vector2f size,
			sf::Vector2f offset,
			unsigned textSize,
			std::vector<std::string> dialogue,
			std::shared_ptr<sf::Font> font);
	virtual ~Dialogue();

	void update();
	void render(sf::RenderTarget& target);

	void setNextLine();

	// Getters / Setters
	// const std::string& getCurrentLine() const;
	bool isEnded() const;
	/*
	unsigned int getCharacterSize() const;
	void setCharacterSize(unsigned int size);
	const sf::String& getString() const;
	void setString(const sf::String& string);
	*/

private:
	// Initialization
	void initVariables();
	void initContainer();
	void initCurrentLine();

	// Resources
	sf::RectangleShape container;
	std::vector<std::string> dialogue;
	std::shared_ptr<sf::Font> font;
	sf::Text currentLine;

	// Variables
	//sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f offset;
	unsigned textSize;

	unsigned lineIndex;
};

} /* namespace gui */

#endif /* GUI_DIALOGUE_HPP_ */
