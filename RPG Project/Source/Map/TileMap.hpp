/*
 * Map.h
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#ifndef MAP_TILEMAP_HPP_
#define MAP_TILEMAP_HPP_

#include "pch.hpp"

// Project
#include "..\Tiles\Tile.hpp"
#include "..\Entities\Entity.hpp"

class TileMap
{
public:
	// Constructor / Destructor
	explicit TileMap(
			sf::Vector2u size,
			float gridSize,
			const std::string& tilesetName,
			unsigned spriteSize);
	virtual ~TileMap();

	// Functions
	void update(sf::Vector2f mousePosView);
	void updateCollisions(std::shared_ptr<Entity> entity);
	void render(
			sf::RenderTarget& target,
			std::shared_ptr<Entity> entity = nullptr);

	void addTile(
			sf::Vector2u index,
			unsigned layer,
			Tile::Type type,
			bool crossable);
	void removeTile(
			sf::Vector2u index,
			unsigned layer);

	// Input / Output
	void saveToFile(const std::string& fileName);
	void loadFromFile(const std::string& fileName);

	// Getters / Setters
	const sf::Texture& getTileset() const;
	bool isActive() const;
	const sf::Vector2u& getSize() const;

	const sf::Vector2u& getSpriteIndex() const;
	void setSpriteIndex(const sf::Vector2u& spriteIndex);
	unsigned getSpriteSize() const;

	/*
	 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	 * Factory method														 *
	 * 																		 *
	 * Every specialization of Map defines what foes and how much of them	 *
	 * should the Party find when encountering a battle. The reference to	 *
	 * Party can be used to know where the party is, letting the concrete	 *
	 * Map decide which enemies to create.									 *
	 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	virtual std::vector<Foe*> getFoes(Party& party) = 0;
	virtual Battle::Background getBackground() = 0;

	const Tile& at(int x, int y);

	int getHeight() const;
	int getWidth() const;
	bool setTile(int x, int y, Tile tile);
	const Tile& getTile(int x, int y) const;
	*/

private:
	// Internal
	void clear();
	void checkMaxValues();
	bool isOutOfBounds(
			sf::Vector2i index,
			bool xAxis = true,
			bool yAxis = true) const;

	// Initialization
	void initVariables();
	void initMap();
	void initTileset();
	void initBorder();
	void initCollisionBox();

	// Resources
	std::vector< std::vector< std::unique_ptr<Tile> > > map;
	sf::Texture tileset;
	//sf::IntRect tileRect;
	sf::RectangleShape border;
	sf::RectangleShape collisionBox;

	// Variables
	bool active;

	//sf::Vector2f position;

	sf::Vector2u size;
	sf::Vector2u maxSize;
	unsigned layers;
	unsigned maxLayers;
	float gridSize;

	std::string tilesetPath;
	std::string tilesetName;
	sf::Vector2u spriteIndex;
	unsigned spriteSize;

	std::string filePath;

	/*
	int width;
	int height;
	std::vector<Tile> field;
	Tile nullTile;
	*/
};

#endif /* MAP_TILEMAP_HPP_ */
