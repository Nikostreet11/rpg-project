/*
 * Map.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#include "TileMap.hpp"

TileMap::TileMap(sf::Vector2u size, float gridSize)
{
	this->gridSize = gridSize;

	//gridSizeU = static_cast<unsigned>(gridSizeF);

	maxSize.x = 18;
	maxSize.y = 10;
	maxLayers = 1;

	if (size.x > maxSize.x)
		size.x = maxSize.x;

	if (size.y > maxSize.y)
		size.y = maxSize.y;

	map.resize(size.x);
	sf::Vector2f tilePosition;

	for (std::size_t x = 0; x < size.x; x++)
	{
		map.push_back(std::vector< std::vector<Tile> >());
		map[x].resize(size.y);
		tilePosition.x = gridSize * x;

		for (std::size_t y = 0; y < size.y; y++)
		{
			map[x].push_back(std::vector<Tile>());
			map[x][y].resize(maxLayers);
			tilePosition.y = gridSize * y;

			for (std::size_t z = 0; z < maxLayers; z++)
			{
				map[x][y].push_back(Tile(tilePosition, gridSize));
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

void TileMap::addTile()
{
}

void TileMap::removeTile()
{
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
