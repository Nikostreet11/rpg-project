/*
 * InnerWindow.hpp
 *
 *  Created on: Mar 25, 2019
 *      Author: nicop
 */

#ifndef SOURCE_GRAPHICS_INNERWINDOW_HPP_
#define SOURCE_GRAPHICS_INNERWINDOW_HPP_

#include "SFML/Graphics.hpp"
#include "../Exclude/Graphics/Node.hpp"

class InnerWindow: public Node {
public:
	explicit InnerWindow(sf::Vector2f size = sf::Vector2f(0, 0));
	virtual ~InnerWindow();

	void virtual onDraw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setSize(sf::Vector2f size);
	const sf::Vector2f& getSize() const;

private:
	sf::RectangleShape rectangle;
};

#endif /* SOURCE_GRAPHICS_INNERWINDOW_HPP_ */
