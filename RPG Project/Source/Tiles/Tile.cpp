/*
 * Tile.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#include "Tile.hpp"

Tile::Tile(
		sf::Vector2i index,
		float size,
		const sf::Texture& tileset,
		sf::Vector2u spriteIndex,
		unsigned spriteSize,
		Type type,
		Closeness closeness,
		bool crossable)
{
	this->type = type;
	this->closeness = closeness;
	this->crossable = crossable;

	sprite.setPosition(sf::Vector2f(
			index.x * size,
			index.y * size));
	sprite.setTexture(tileset);
	sprite.setTextureRect(sf::IntRect(
			spriteIndex.x * spriteSize,
			spriteIndex.y * spriteSize,
			spriteSize,
			spriteSize));
	sprite.setScale(sf::Vector2f(
			size / spriteSize,
			size / spriteSize));
}

Tile::~Tile() {
}

void Tile::update()
{
}

void Tile::render(
		sf::RenderTarget& target,
		const sf::RenderStates& states)
{
	target.draw(sprite, states);
}

const std::string Tile::getAsString() const
{
	std::stringstream stringStream;

	stringStream <<
			getSpriteIndex().x << ' ' <<
			getSpriteIndex().y << ' ' <<
			type << ' ' <<
			closeness << ' ' <<
			crossable << '\n';

	return stringStream.str();
}

// Getters / Setters
Tile::Type Tile::getType() const
{
	return type;
}

void Tile::setType(Type type)
{
	this->type = type;
}

Tile::Closeness Tile::getCloseness() const
{
	return closeness;
}

bool Tile::isCrossable() const
{
	return crossable;
}

const sf::Vector2f& Tile::getPosition() const
{
	return sprite.getPosition();
}

sf::Vector2f Tile::getSize() const
{
	return sf::Vector2f(
			sprite.getScale().x * sprite.getTextureRect().width,
			sprite.getScale().y * sprite.getTextureRect().height);
}

sf::FloatRect Tile::getGlobalBounds() const
{
	return sprite.getGlobalBounds();
}

sf::Vector2u Tile::getSpriteIndex() const
{
	return sf::Vector2u(
			sprite.getTextureRect().left / sprite.getTextureRect().width,
			sprite.getTextureRect().top / sprite.getTextureRect().height);
}

sf::Vector2u Tile::getSpriteSize() const
{
	return sf::Vector2u(
			sprite.getTextureRect().width,
			sprite.getTextureRect().height);
}

const sf::IntRect& Tile::getTextureRect() const
{
	return sprite.getTextureRect();
}

std::string Tile::to_string(Type type)
{
	switch (type)
	{
	case 0:
		return "Default";
		break;

	case 1:
		return "Damaging";
		break;

	case 2:
		return "Dangerous";
		break;

	default:
		return std::to_string(type);
	}
}

std::string Tile::to_string(Closeness closeness)
{
	switch (closeness)
	{
	case 0:
		return "Background";
		break;

	case 1:
		return "Foreground";
		break;

	default:
		return std::to_string(closeness);
	}
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
