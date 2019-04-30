/*
 * Tile.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#include "Tile.h"

Tile::Tile() : /*texture(villages), */tileType(TileType::nullType) {
	updateInfo(/*texture, */tileType);
}

Tile::Tile(/*Texture texture, */TileType tileType) :
		/*texture(texture), */tileType(tileType) {
	updateInfo(/*texture, */tileType);
}

Tile::~Tile() {}
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

bool Tile::updateInfo(/*Texture texture, */TileType tileType) {
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

/*Texture Tile::getTexture() const {
	return texture;
}*/

const TileType Tile::getTileType() const {
	return tileType;
}

bool Tile::isDangerous() const {
	return dangerous;
}
