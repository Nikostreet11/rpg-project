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

Tile::Tile(
		sf::Vector2f position,
		float gridSize,
		const sf::Texture& tileTextureSheet,
		sf::IntRect textureRect)
{
	shape.setSize(sf::Vector2f(gridSize, gridSize));
	shape.setFillColor(sf::Color::White);
	//shape.setOutlineThickness(1.f);
	//shape.setOutlineColor(sf::Color::Black);
	shape.setPosition(position);
	shape.setTexture(&tileTextureSheet);
	shape.setTextureRect(textureRect);
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

const sf::IntRect& Tile::getTextureRect() const
{
	return shape.getTextureRect();
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
