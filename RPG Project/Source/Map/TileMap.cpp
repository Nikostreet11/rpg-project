/*
 * Map.cpp
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#include "TileMap.hpp"

TileMap::TileMap(
		sf::Vector2u size,
		unsigned maxLayers,
		float gridSize,
		const std::string& tilesetName,
		unsigned spriteSize,
		std::map<std::string, std::shared_ptr<sf::Texture>> textures,
		std::shared_ptr<sf::Font> font)
{
	initVariables();

	//this->position = position;
	this->size = size;
	this->maxLayers = maxLayers;
	//this->layers = maxLayers;
	this->gridSize = gridSize;

	this->tilesetName = tilesetName;
	this->spriteSize = spriteSize;

	this->textures = textures;
	this->font = font;

	checkMaxValues();

	initMap();
	initTileset();
	initBorder();
	initCollisionBox();
	initTilesCounter();
}

TileMap::~TileMap()
{
}

// Functions
void TileMap::update(sf::Vector2f mousePosView)
{
	if (border.getGlobalBounds().contains(mousePosView))
	{
		active = true;
	}
	else
	{
		active = false;
	}
}

void TileMap::updateBoundsCollisions(
		std::shared_ptr<Entity> entity,
		const float& dt)
{
	if (entity->getNextPosition(dt).x < 0.f)
	{
		entity->stop(Axis::X);
		entity->setPosition(sf::Vector2f(
				0.f,
				entity->getPosition().y));
	}

	if (entity->getNextPosition(dt).x + entity->getSize().x >
				size.x * gridSize)
	{
		entity->stop(Axis::X);
		entity->setPosition(sf::Vector2f(
				size.x * gridSize - entity->getSize().x,
				entity->getPosition().y));
	}

	if (entity->getNextPosition(dt).y < 0.f)
	{
		entity->stop(Axis::Y);
		entity->setPosition(sf::Vector2f(
				entity->getPosition().x,
				0.f));
	}

	if (entity->getNextPosition(dt).y + entity->getSize().y >
				size.y * gridSize)
	{
		entity->stop(Axis::Y);
		entity->setPosition(sf::Vector2f(
				entity->getPosition().x,
				size.y * gridSize - entity->getSize().y));
	}
}

void TileMap::updateTilesCollisions(
		std::shared_ptr<Entity> entity,
		const float& dt)
{
	sf::Vector2i cullingStartInt = {
			static_cast<int>(entity->getNextPosition(dt).x / gridSize) - 1,
			static_cast<int>(entity->getNextPosition(dt).y / gridSize) - 1};

	sf::Vector2f cullingEndFloat = {
			(entity->getNextPosition(dt).x + entity->getSize().x) / gridSize,
			(entity->getNextPosition(dt).y + entity->getSize().y) / gridSize};

	sf::Vector2i cullingEndInt = {
			static_cast<int>(cullingEndFloat.x) + 2,
			static_cast<int>(cullingEndFloat.y) + 2};

	if (cullingEndFloat.x == std::floor(cullingEndFloat.x))
	{
		cullingEndInt.x--;
	}

	if (cullingEndFloat.y == std::floor(cullingEndFloat.y))
	{
		cullingEndInt.y--;
	}

	sf::Vector2u cullingStart = checkBounds(cullingStartInt);
	sf::Vector2u cullingEnd = checkBounds(cullingEndInt);

	for (std::size_t x = cullingStart.x; x < cullingEnd.x; x++)
	{
		for (std::size_t y = cullingStart.y; y < cullingEnd.y; y++)
		{
			std::vector<std::unique_ptr<Tile>>& tileList = map[y * size.x + x];

			for (std::size_t layer = 0; layer < tileList.size(); layer++)
			{
				Tile& tile = *map[y * size.x + x][layer];

				sf::Vector2f entityPos = entity->getPosition();
				sf::Vector2f entitySize = entity->getSize();
				sf::Vector2f tilePos = tile.getPosition();
				sf::Vector2f tileSize = tile.getSize();

				if (!tile.isCrossable() &&
					entity->getNextGlobalBounds(dt).intersects(
							tile.getGlobalBounds()))
				{
					if (entityPos.x > tilePos.x
						&& entityPos.x + entitySize.x > tilePos.x + tileSize.x
						&& entityPos.y < tilePos.y + tileSize.y
						&& entityPos.y + entitySize.y > tilePos.y)
					{
						// Left collision
						entity->stop(Axis::X);
						entity->setPosition(sf::Vector2f(
								tilePos.x + tileSize.x,
								entityPos.y));
					}
					else if (entityPos.x < tilePos.x
						&& entityPos.x + entitySize.x < tilePos.x + tileSize.x
						&& entityPos.y < tilePos.y + tileSize.y
						&& entityPos.y + entitySize.y > tilePos.y)
					{
						// Right collision
						entity->stop(Axis::X);
						entity->setPosition(sf::Vector2f(
								tilePos.x - entitySize.x,
								entityPos.y));
					}

					if (entityPos.y > tilePos.y
						&& entityPos.y + entitySize.y > tilePos.y + tileSize.y
						&& entityPos.x < tilePos.x + tileSize.x
						&& entityPos.x + entitySize.x > tilePos.x)
					{
						// Top collision
						entity->stop(Axis::Y);
						entity->setPosition(sf::Vector2f(
								entityPos.x,
								tilePos.y + tileSize.y));
					}
					else if (entityPos.y < tilePos.y
						&& entityPos.y + entitySize.y < tilePos.y + tileSize.y
						&& entityPos.x < tilePos.x + tileSize.x
						&& entityPos.x + entitySize.x > tilePos.x)
					{
						// Bottom collision
						entity->stop(Axis::Y);
						entity->setPosition(sf::Vector2f(
								entityPos.x,
								tilePos.y - entitySize.y));
					}
				}
			}
		}
	}
}

void TileMap::render(sf::RenderTarget& target, Tile::Closeness closeness)
{
	for (auto &tile : map)
	{
		for (auto layer = tile.begin(); layer < tile.end(); layer++)//auto &layer : tile)
		{
			if (*layer != nullptr)
			{
				if ((*layer)->getCloseness() == closeness)
				{
					(*layer)->render(target);

					if (editorMode)
					{
						if (!(*layer)->isCrossable())
						{
							collisionBox.setPosition((*layer)->getPosition());
							target.draw(collisionBox);
						}

						/*
						if (layer == tile.end() - 1)
						{
							tilesCounter.setPosition((*layer)->getPosition());
							tilesCounter.setString(std::to_string(tile.size()));
							target.draw(tilesCounter);
						}
						*/
					}
				}
			}
		}
	}

	if (closeness == Tile::Background)
	{
		target.draw(border);
	}
}

void TileMap::addTile(
		sf::Vector2u index,
		Tile::Type type,
		Tile::Closeness closeness,
		bool crossable)
{
	if (0 <= index.x && index.x < size.x &&
		0 <= index.y && index.y < size.y &&
		map[index.y * size.x + index.x].size() < maxLayers)
	{
		/*if (map[index.y * size.x + index.x][layers] == nullptr)
		{*/
		sf::Vector2f tilePosition;
		tilePosition.x = index.x * gridSize;
		tilePosition.y = index.y * gridSize;

		std::unique_ptr<Tile> tilePtr(new Tile(
				static_cast<sf::Vector2i>(index),
				gridSize,
				tileset,
				spriteIndex,
				spriteSize,
				type,
				closeness,
				crossable));

		map[index.y * size.x + index.x].push_back(std::move(tilePtr));
		//}
	}
}

void TileMap::addBaseTile(
		sf::Vector2u index,
		Tile::Type type,
		Tile::Closeness closeness,
		bool crossable)
{
	if (0 <= index.x && index.x < size.x &&
		0 <= index.y && index.y < size.y)
	{
		/*if (map[index.y * size.x + index.x][layers] == nullptr)
		{*/
		sf::Vector2f tilePosition;
		tilePosition.x = index.x * gridSize;
		tilePosition.y = index.y * gridSize;

		std::unique_ptr<Tile> tilePtr(new Tile(
				static_cast<sf::Vector2i>(index),
				gridSize,
				tileset,
				spriteIndex,
				spriteSize,
				type,
				closeness,
				crossable));

		map[index.y * size.x + index.x].clear();
		map[index.y * size.x + index.x].push_back(std::move(tilePtr));
		//}
	}
}

void TileMap::removeTile(sf::Vector2u index)
{
	if (0 <= index.x && index.x < size.x &&
		0 <= index.y && index.y < size.y &&
		map[index.y * size.x + index.x].size() > 0)
	{
		/*if (map[index.y * size.x + index.x][layer] != nullptr)
		{*/

		map[index.y * size.x + index.x].pop_back();
		//}
	}
}

void TileMap::saveToFile(const std::string& fileName)
{
	/* Saves the entire tilemap to a text file
	 *
	 * ---------- Format ----------
	 * sizeX sizeY sizeZ
	 * textureName
	 * spriteSize
	 *
	 * tileX tileY tileZ spriteX spriteY type closeness collision
	 */

	std::ofstream outFile;

	outFile.open(filePath + fileName);

	if (outFile.is_open())
	{
		outFile <<
				size.x << ' ' << size.y << ' ' << maxLayers << '\n' <<
				tilesetName << '\n' <<
				spriteSize << '\n';

		for (std::size_t index = 0; index < size.x * size.y; index++)
		{
			for (std::size_t layer = 0; layer < map[index].size(); layer++)
			{
				/*if (map[index][layer] != nullptr)
				{*/
				outFile <<
						index % size.x << ' ' <<
						index / size.x << ' ' <<
						layer << ' ';

				outFile << map[index][layer]->getAsString();
				//}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD_NOT_SAVE_TO_FILE::FILEPATH: " <<
				fileName << std::endl;
	}

	outFile.close();
}

void TileMap::loadFromFile(const std::string& fileName)
{
	clear();

	std::ifstream inFile;

	inFile.open(filePath + fileName);

	if (inFile.is_open())
	{
		inFile >>
				size.x >> size.y >> maxLayers >>
				tilesetName >>
				spriteSize;

		/*
		tileRect.width = spritesSize;
		tileRect.height = spritesSize;
		*/

		if (size.x > maxSize.x)
			size.x = maxSize.x;

		if (size.y > maxSize.y)
			size.y = maxSize.y;

		map.resize(size.x * size.y);
		/*for (std::size_t index = 0; index < size.x * size.y; index++)
		{
			map[index].resize(layers);
		}*/

		if (!tileset.loadFromFile(tilesetPath + tilesetName))
		{
			std::cout << "ERROR::TILEMAP::FAILED_TO_LOAD_TILESHEET" << std::endl;
		}

		std::size_t x, y, layer;
		//sf::Vector2u spriteIndex;
		short type, closeness;
		bool crossable;

		while (inFile
				>> x
				>> y
				>> layer
				>> spriteIndex.x
				>> spriteIndex.y
				>> type
				>> closeness
				>> crossable)
		{
			sf::Vector2f tilePosition;
			tilePosition.x = x * gridSize;
			tilePosition.y = y * gridSize;

			/*
			tileRect.left = sprite.x * spritesSize;
			tileRect.top = sprite.y * spritesSize;
			*/

			std::unique_ptr<Tile> tilePtr(new Tile(
					sf::Vector2i(x, y),
					gridSize,
					tileset,
					spriteIndex,
					spriteSize,
					static_cast<Tile::Type>(type),
					static_cast<Tile::Closeness>(closeness),
					crossable));

			if (layer == map[y * size.x + x].size()
				&& layer < maxLayers)
			{
				map[y * size.x + x].push_back(std::move(tilePtr));
			}
		}

		border.setSize(sf::Vector2f(
				size.x * gridSize,
				size.y * gridSize));
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD_NOT_LOAD_FROM_FILE::FILEPATH: " <<
				fileName << std::endl;
	}

	inFile.close();
}

// Getters / Setters
bool TileMap::isDangerousAt(sf::FloatRect rectangle)
{
	bool danger = false;

	sf::Vector2u cullingStart =
	{
		static_cast<unsigned>(rectangle.left / gridSize),
		static_cast<unsigned>(rectangle.top / gridSize)
	};

	sf::Vector2u cullingEnd =
	{
		static_cast<unsigned>(
				(rectangle.left + rectangle.width) / gridSize) + 1,
		static_cast<unsigned>(
				(rectangle.top + rectangle.height) / gridSize) + 1
	};

	for (size_t y = cullingStart.y; y < cullingEnd.y; y++)
	{
		for (size_t x = cullingStart.x; x < cullingEnd.x; x++)
		{
			for (auto& layer : map[y * size.x + x])
			{
				if (layer->getType() == Tile::Dangerous)
				{
					danger = true;
				}
			}
		}
	}

	return danger;
}

const sf::Texture& TileMap::getTileset() const
{
	return tileset;
}

bool TileMap::isActive() const
{
	return active;
}

void TileMap::setEditorMode(bool editorMode)
{
	this->editorMode = editorMode;
}

const sf::Vector2u& TileMap::getSize() const
{
	return size;
}

const sf::Vector2u& TileMap::getSpriteIndex() const
{
	return spriteIndex;
}

void TileMap::setSpriteIndex(const sf::Vector2u& spriteIndex)
{
	this->spriteIndex = spriteIndex;
}

unsigned TileMap::getSpriteSize() const
{
	return spriteSize;
}

// Internal
void TileMap::clear()
{
	for (std::size_t index = 0; index < map.size(); index++)
	{
		for (std::size_t layer = 0; layer < map[index].size(); layer++)
		{
			map[index].clear();
		}
	}
}

void TileMap::checkMaxValues()
{
	if (this->size.x > maxSize.x)
	{
		this->size.x = maxSize.x;
	}

	if (this->size.y > maxSize.y)
	{
		this->size.y = maxSize.y;
	}
}

sf::Vector2u TileMap::checkBounds(const sf::Vector2i& index)
{
	sf::Vector2u newIndex;

	newIndex.x = (index.x < 0)
			? 0
			: static_cast<unsigned>(index.x);

	newIndex.x = (index.x > static_cast<int>(size.x))
			? static_cast<int>(size.x)
			: newIndex.x;

	newIndex.y = (index.y < 0)
			? 0
			: static_cast<unsigned>(index.y);

	newIndex.y = (index.y > static_cast<int>(size.y))
			? static_cast<int>(size.y)
			: newIndex.y;

	return newIndex;
}

bool TileMap::isOutOfBounds(sf::Vector2u index, Axis axis) const
{
	switch (axis)
	{
	case Axis::X:
		if (index.x >= size.x)
		{
			return true;
		}
		break;

	case Axis::Y:
		if (index.y >= size.y)
		{
			return true;
		}
		break;

	case Axis::NoAxis:
		if (index.x >= size.x || index.y >= size.y)
		{
			return true;
		}
		break;
	}

	return false;
}

// Initialization
void TileMap::initVariables()
{
	active = false;
	editorMode = false;

	maxSize.x = 100;
	maxSize.y = 100;
	//maxLayers = 3;
	//layers = 0;
	gridSize = 0;

	tilesetPath = "Images/Exploration/Tilesets/";
	tilesetName = "";
	spriteSize = 0;

	filePath = "Data/Tilemaps/";
}

void TileMap::initMap()
{
	map.resize(size.x * size.y);
	/*
	sf::Vector2f tilePosition;

	for (std::size_t index = 0; index < size.x * size.y; index++)
	{
		map[index].resize(layers);

		for (std::size_t layer = 0; layer < layers; layer++)
		{
			map[index][layer] = nullptr;
		}
	}
	*/
}

void TileMap::initTileset()
{
	if (!tileset.loadFromFile(tilesetPath + tilesetName))
	{
		std::cout << "ERROR::TILEMAP::FAILED_TO_LOAD_TILESHEET" << std::endl;
	}
}

void TileMap::initBorder()
{
	//border.setPosition(position);
	border.setSize(sf::Vector2f(
			size.x * gridSize,
			size.y * gridSize));
	border.setFillColor(sf::Color::Transparent);
	border.setOutlineThickness(3);
	border.setOutlineColor(sf::Color::Red);
}

void TileMap::initCollisionBox()
{
	collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
}

void TileMap::initTilesCounter()
{
	tilesCounter.setFont(*font);
	tilesCounter.setCharacterSize(30);
	tilesCounter.setFillColor(sf::Color::White);
	tilesCounter.setOutlineThickness(1.f);
	tilesCounter.setOutlineColor(sf::Color::Black);
}

/*
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
