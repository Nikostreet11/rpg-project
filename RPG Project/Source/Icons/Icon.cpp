/*
 * Icon.cpp
 *
 *  Created on: Apr 2, 2019
 *      Author: nicop
 */

#include "Icon.hpp"

Icon::Icon()
{
	//aspectRatio = 1;
	size = 0;
	color = sf::Color::Black;
}

Icon::~Icon()
{
}

float Icon::getSize() const
{
	return size;
}

/*void Icon::setSize(const sf::Vector2f& size) {
	this->size = size;
	update();
}*/

void Icon::setSize(float size)
{
	this->size = size;//sf::Vector2f(size * aspectRatio, size);
	update();
}

const sf::Color& Icon::getColor() const
{
	return color;
}

void Icon::setColor(const sf::Color& color)
{
	this->color = color;
	update();
}
