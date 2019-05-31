/*
 * Map.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#include "TileMap.hpp"

TileMap::TileMap(sf::Vector2f position, sf::Vector2u size, float gridSize)
{
	initVariables();

	this->position = position;
	this->size = size;
	this->layers = maxLayers;
	this->gridSize = gridSize;

	//gridSizeU = static_cast<unsigned>(gridSizeF);

	if (size.x > maxSize.x)
		size.x = maxSize.x;

	if (size.y > maxSize.y)
		size.y = maxSize.y;

	map.resize(size.x * size.y);
	sf::Vector2f tilePosition;

	for (std::size_t index = 0; index < map.size(); index++)
	{
		map[index].resize(maxLayers);

		for (std::size_t layer = 0; layer < layers; layer++)
		{
			map[index][layer] = nullptr;
		}
	}

	if (!tileSheet.loadFromFile("Images/Exploration/Tilesets/Villages.png"))
	{
		std::cout << "ERROR::TILEMAP::FAILED_TO_LOAD_TILETEXTURESHEET" << std::endl;
	}

	border.setPosition(position);
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

void TileMap::update(sf::Vector2f mousePosView)
{
	if (mousePosView.x - position.x < 0)
	{
		mousePosGrid.x = 0;
	}
	else
	{
		mousePosGrid.x =
				static_cast<unsigned>((mousePosView.x - position.x) / gridSize);
	}

	if (mousePosView.y - position.y < 0)
	{
		mousePosGrid.y = 0;
	}
	else
	{
		mousePosGrid.y =
				static_cast<unsigned>((mousePosView.y - position.y) / gridSize);
	}

	if (mousePosGrid.x >= size.x)
	{
		mousePosGrid.x = size.x - 1;
	}
	if (mousePosGrid.y >= size.y)
	{
		mousePosGrid.y = size.y - 1;
	}
}

void TileMap::render(std::shared_ptr<sf::RenderTarget> target)
{
	for (auto &tile : map)
	{
		for (auto &layer : tile)
		{
			if (layer != nullptr)
			{
				layer->render(target);
			}
		}
	}

	target->draw(border);
}

void TileMap::addTile(sf::Vector2u index, unsigned layer)
{
	if (0 <= index.x && index.x < size.x &&
		0 <= index.y && index.y < size.y &&
		0 <= layer && layer < layers)
	{
		if (map[index.y * size.x + index.x][layer] == nullptr)
		{
			sf::Vector2f tilePosition;
			tilePosition.x = index.x * gridSize + this->position.x;
			tilePosition.y = index.y * gridSize + this->position.y;

			std::unique_ptr<Tile> tilePtr(new Tile(
					tilePosition,
					gridSize,
					tileSheet,
					tileRect));
			map[index.y * size.x + index.x][layer] = std::move(tilePtr);
		}
	}
}

void TileMap::addTile(unsigned layer)
{
	addTile(mousePosGrid, layer);
}

void TileMap::removeTile(sf::Vector2u index, unsigned layer)
{
	if (0 <= index.x && index.x < size.x &&
		0 <= index.y && index.y < size.y &&
		0 <= layer && layer < layers)
	{
		if (map[index.y * size.x + index.x][layer] != nullptr)
		{
			map[index.y * size.x + index.x][layer].reset();
		}
	}
}

void TileMap::removeTile(unsigned layer)
{
	removeTile(mousePosGrid, layer);
}

void TileMap::selectNextTile()
{
	tileRect.left = 0;
	tileRect.top = 32;
}

void TileMap::selectPreviousTile()
{
	tileRect.left = 64;
	tileRect.top = 0;
}

const sf::Texture& TileMap::getTileSheet() const
{
	return tileSheet;
}

const sf::IntRect& TileMap::getTileRect() const
{
	return tileRect;
}

void TileMap::initVariables()
{
	maxSize.x = 20;
	maxSize.y = 15;
	maxLayers = 1;
	gridSize = 0;

	tileRect = sf::IntRect(64, 0, 32, 32);
}

void TileMap::initMap()
{
	// TODO
}

void TileMap::initBorder()
{
	// TODO
}

void TileMap::setTileRect(const sf::IntRect& tileRect)
{
	this->tileRect = tileRect;
}

const sf::Vector2f& TileMap::getPosition() const
{
	return position;
}

const sf::Vector2u& TileMap::getMousePosGrid() const
{
	return mousePosGrid;
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
