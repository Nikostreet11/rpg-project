/*
 * Node.hpp
 *
 *  Created on: Mar 20, 2019
 *      Author: nicop
 */

#ifndef SOURCE_GRAPHICS_NODE_HPP_
#define SOURCE_GRAPHICS_NODE_HPP_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <vector>

class Node: public sf::Transformable, public sf::Drawable {
public:
	bool addChild(Node& node);
	bool removeChild();

	void draw(sf::RenderTarget& target, sf::RenderStates parentStates) const;
	void virtual onDraw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	Node();
	virtual ~Node();

private:
	std::vector<Node*> children;
};

#endif /* SOURCE_GRAPHICS_NODE_HPP_ */
