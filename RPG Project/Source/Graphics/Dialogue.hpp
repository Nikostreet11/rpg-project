/*
 * Dialogue.hpp
 *
 *  Created on: Mar 25, 2019
 *      Author: nicop
 */

#ifndef SOURCE_GRAPHICS_DIALOGUE_HPP_
#define SOURCE_GRAPHICS_DIALOGUE_HPP_

#include "Node.hpp"

#include <SFML/Graphics.hpp>

class Dialogue: public Node {
public:
	Dialogue(unsigned int characterSize = 0, sf::String string = "");
	virtual ~Dialogue();

	void virtual onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

	unsigned int getCharacterSize() const;
	void setCharacterSize(unsigned int size);
	const sf::String& getString() const;
	void setString(const sf::String& string);

private:
	sf::Text text;
	sf::Font font;
};

#endif /* SOURCE_GRAPHICS_DIALOGUE_HPP_ */
