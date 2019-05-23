/*
 * Tile.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#include "Tile.hpp"

Tile::Tile()
{
}

Tile::Tile(sf::Vector2f position, float gridSizeF)
{
	shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(position);
}

Tile::~Tile() {
}

void Tile::update()
{
}

void Tile::render(std::shared_ptr<sf::RenderTarget> target)
{
	target->draw(shape);
}
/*
Tile& Tile::operator=(const Tile& entry) {
	if (this != &entry) {
		//texture = entry.getTexture();
		tileType = entry.getTileType();
		crossable = entry.isCrossable();
		dangerous = entry.isDangerous();
	}
	return *this;
}

bool Tile::isCrossable() const {
	return crossable;
}

bool Tile::updateInfo(Texture texture, TileType tileType) {
	crossable = true;
	dangerous = false;

	switch (tileType) {
	case TileType::nullType:
		crossable = false;
		break;
	case TileType::grass:
		break;
	case TileType::bush:
		dangerous = true;
		break;
	case TileType::tree:
		crossable = false;
		break;
	case TileType::root:
		crossable = false;
		break;
	// TODO: other cases
	default:
		return false;
	}

	return true;
}

Texture Tile::getTexture() const {
	return texture;
}

const TileType Tile::getTileType() const {
	return tileType;
}

bool Tile::isDangerous() const {
	return dangerous;
}
*/
