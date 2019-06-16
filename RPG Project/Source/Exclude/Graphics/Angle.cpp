/*
 * Angle.cpp
 *
 *  Created on: Apr 2, 2019
 *      Author: nicop
 */

#include "../Exclude/Graphics/Angle.hpp"

namespace icons {

Angle::Angle() {
	update();
}

Angle::~Angle() {}

void Angle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	states.transform *= this->getTransform();
	target.draw(vertexArray, states);
}

void Angle::update() {
	loadVertexArray();

	/*sf::FloatRect bounds = vertexArray.getBounds();
	aspectRatio = bounds.width / bounds.height;*/
	for (std::size_t index = 0; index < vertexArray.getVertexCount(); index++) {
		vertexArray[index].position.x *= size;//.x / bounds.width;
		vertexArray[index].position.y *= size;//.y / bounds.height;
		vertexArray[index].color = color;
	}
}

void Angle::loadVertexArray() {
	vertexArray.setPrimitiveType(sf::TriangleStrip);
	vertexArray.resize(6);

	vertexArray[0].position = sf::Vector2f(.2, .1);
	vertexArray[1].position = sf::Vector2f(.3, 0);
	vertexArray[2].position = sf::Vector2f(.6, .5);
	vertexArray[3].position = sf::Vector2f(.8, .5);
	vertexArray[4].position = sf::Vector2f(.2, .9);
	vertexArray[5].position = sf::Vector2f(.3, 1);
}

} /* namespace icons */
