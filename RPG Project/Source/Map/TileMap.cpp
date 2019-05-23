/*
 * Map.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#include "TileMap.hpp"

#include "../Randomizer.h"

#include "../Texture.h"

TileMap::TileMap()
{
	gridSizeF = 50.f;
	gridSizeU = static_cast<unsigned>(gridSizeF);
	maxSize.x = 40;
	maxSize.y = 25;
	maxLayers = 1;

	map.resize(maxSize.x);
	sf::Vector2f tilePosition;

	for (std::size_t x = 0; x < maxSize.x; x++)
	{
		map.push_back(std::vector< std::vector<Tile> >());
		map[x].resize(maxSize.y);
		tilePosition.x = gridSizeF * x;

		for (std::size_t y = 0; y < maxSize.y; y++)
		{
			map[x].push_back(std::vector<Tile>());
			map[x][y].resize(maxLayers);
			tilePosition.y = gridSizeF * y;

			for (std::size_t z = 0; z < maxLayers; z++)
			{
				map[x][y].push_back(Tile(tilePosition, gridSizeF));
			}
		}

	}
}

TileMap::~TileMap()
{
}

void TileMap::update()
{
}

void TileMap::render(std::shared_ptr<sf::RenderTarget> target)
{
	for (auto &x : map)
	{
		for (auto &y : x)
		{
			for (auto &layer : y)
			{
				layer.render(target);
			}
		}
	}
}
/*
bool TileMap::isOutOfBounds(int posX, int posY) const {
	if (posX < 0 || posX >= width || posY < 0 || posY >= height)
		return true;
	else
		return false;
}

const Tile& TileMap::at(int x, int y) {
	return getTile(x, y);
}

bool TileMap::setTile(int x, int y, Tile tile) {
	if (isOutOfBounds(x, y))
		return false;
	else {
		field.at(width * y + x) = tile;
		return true;
	}
}

const Tile& TileMap::getTile(int x, int y) const {
	if (isOutOfBounds(x, y)) {
		return nullTile;
	}
	else {
		return field.at(width * y + x);
	}
}

int TileMap::getHeight() const {
	return height;
}

int TileMap::getWidth() const {
	return width;
}
*/
