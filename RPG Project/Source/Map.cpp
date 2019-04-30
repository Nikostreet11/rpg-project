/*
 * Map.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#include "Map.h"

#include "Randomizer.h"

#include "Texture.h"

Map::Map(int w, int h) : width(w), height(h), field(w * h) {}

Map::~Map() {}

bool Map::isOutOfBounds(int posX, int posY) const {
	if (posX < 0 || posX >= width || posY < 0 || posY >= height)
		return true;
	else
		return false;
}

const Tile& Map::at(int x, int y) {
	return getTile(x, y);
}

bool Map::setTile(int x, int y, Tile tile) {
	if (isOutOfBounds(x, y))
		return false;
	else {
		field.at(width * y + x) = tile;
		return true;
	}
}

const Tile& Map::getTile(int x, int y) const {
	if (isOutOfBounds(x, y)) {
		return nullTile;
	}
	else {
		return field.at(width * y + x);
	}
}

int Map::getHeight() const {
	return height;
}

int Map::getWidth() const {
	return width;
}
