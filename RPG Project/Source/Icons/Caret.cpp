/*
 * Caret.cpp
 *
 *  Created on: Apr 1, 2019
 *      Author: nicop
 */

#include "Caret.hpp"

namespace icons
{

Caret::Caret()
{
	update();
}

Caret::~Caret() {}

void Caret::render(sf::RenderTarget& target)
{
	sf::RenderStates states;
	states.transform *= this->getTransform();
	target.draw(vertexArray, states);
}

void Caret::update()
{
	loadVertexArray();

	// sf::FloatRect bounds = vertexArray.getBounds();
	// aspectRatio = bounds.width / bounds.height;
	for (std::size_t index = 0; index < vertexArray.getVertexCount(); index++) {
		vertexArray[index].position.x *= size;//.x / bounds.width;
		vertexArray[index].position.y *= size;//.y / bounds.height;
		vertexArray[index].color = color;
	}
}

void Caret::loadVertexArray()
{
	vertexArray.setPrimitiveType(sf::TriangleStrip);
	vertexArray.resize(5);

	vertexArray[0].position = sf::Vector2f(.3, 0);
	vertexArray[1].position = sf::Vector2f(.2, .1);
	vertexArray[2].position = sf::Vector2f(.8, .5);
	vertexArray[3].position = sf::Vector2f(.2, .9);
	vertexArray[4].position = sf::Vector2f(.3, 1);
}

} /* namespace icons */
