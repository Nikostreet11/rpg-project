/*
 * Map.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#include "TileMap.hpp"

TileMap::TileMap(sf::Vector2u size, float gridSize)
{
	initVariables();

	this->gridSize = gridSize;

	//gridSizeU = static_cast<unsigned>(gridSizeF);

	if (size.x > maxSize.x)
		size.x = maxSize.x;

	if (size.y > maxSize.y)
		size.y = maxSize.y;

	map.resize(size.x);
	sf::Vector2f tilePosition;

	for (std::size_t x = 0; x < size.x; x++)
	{
		map[x].resize(size.y);
		//tilePosition.x = gridSize * x;

		for (std::size_t y = 0; y < size.y; y++)
		{
			map[x][y].resize(maxLayers);
			//tilePosition.y = gridSize * y;

			for (std::size_t z = 0; z < maxLayers; z++)
			{
				//std::unique_ptr<Tile> tilePtr(new Tile(tilePosition, gridSize));
				map[x][y][z] = nullptr;//std::move(tilePtr);
			}
		}
	}

	if (!tileTextureSheet.loadFromFile("Images/Exploration/Tilesets/Villages.png"))
	{
		std::cout << "ERROR::TILEMAP::FAILED_TO_LOAD_TILETEXTURESHEET" << std::endl;
	}

	border.setSize(sf::Vector2f(
			size.x * gridSize,
			size.y * gridSize));
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(3);
	border.setOutlineColor(sf::Color::Red);
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
				if (layer != nullptr)
				{
					layer->render(target);
				}
			}
		}
	}

	target->draw(border);
}

void TileMap::addTile(sf::Vector2u position, unsigned z, sf::IntRect rect)
{
	if (0 <= position.x && position.x < map.size() &&
			0 <= position.y && position.y < map[position.x].size() &&
			0 <= z && z < map[position.x][position.y].size())
	{
		if (map[position.x][position.y][z] == nullptr)
		{
			sf::Vector2f tilePosition;
			tilePosition.x = position.x * gridSize;
			tilePosition.y = position.y * gridSize;
			std::unique_ptr<Tile> tilePtr(new Tile(
					tilePosition,
					gridSize,
					tileTextureSheet,
					rect));
			map[position.x][position.y][z] = std::move(tilePtr);
		}
	}
}

void TileMap::removeTile(sf::Vector2u position, unsigned z)
{
	if (0 <= position.x && position.x < map.size() &&
			0 <= position.y && position.y < map[position.x].size() &&
			0 <= z && z < map[position.x][position.y].size())
	{
		if (map[position.x][position.y][z] != nullptr)
		{
			map[position.x][position.y][z].reset();
		}
	}
}

void TileMap::initVariables()
{
	maxSize.x = 20;
	maxSize.y = 15;
	maxLayers = 1;
	gridSize = 0;
}

void TileMap::initMap()
{
	// TODO
}

void TileMap::initBorder()
{
	// TODO
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
