/*
 * Map.h
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#ifndef MAP_TILEMAP_HPP_
#define MAP_TILEMAP_HPP_

#include "..\PCH\pch.hpp"

// Project
#include "..\Tiles\Tile.hpp"

class TileMap
{
public:
	explicit TileMap(
			sf::Vector2f position,
			sf::Vector2u size,
			float gridSize,
			const std::string& textureName,
			unsigned spriteSize);
	virtual ~TileMap();

	// Functions
	void update(sf::Vector2f mousePosView);
	void render(std::shared_ptr<sf::RenderTarget> target);

	void addTile(sf::Vector2u index, unsigned layer);
	void addTile(unsigned layer);
	void removeTile(sf::Vector2u index, unsigned layer);
	void removeTile(unsigned layer);

	void saveToFile(const std::string& fileName);
	void loadFromFile(const std::string& fileName);

	// Getters / Setters
	bool isActive() const;
	const sf::Texture& getTileSheet() const;
	const sf::IntRect& getTileRect() const;
	void setTile(const sf::IntRect& tileRect);
	const sf::Vector2f& getPosition() const;
	const sf::Vector2u& getMousePosGrid() const;

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

	bool isOutOfBounds(int posX, int posY) const;
	const Tile& at(int x, int y);

	int getHeight() const;
	int getWidth() const;
	bool setTile(int x, int y, Tile tile);
	const Tile& getTile(int x, int y) const;
	*/

private:
	void clear();

	// Initialization
	void initVariables();
	void initMap();
	void initBorder();

	// Resources
	std::vector< std::vector< std::unique_ptr<Tile> > > map;
	sf::Texture tileSheet;
	sf::IntRect tileRect;
	sf::RectangleShape border;

	// Variables
	bool active;

	sf::Vector2f position;
	sf::Vector2u size;
	sf::Vector2u maxSize;
	unsigned layers;
	unsigned maxLayers;
	float gridSize;

	std::string texturePath;
	std::string textureName;
	unsigned spriteSize;
	std::string filePath;

	sf::Vector2u mousePosGrid;

	/*
	int width;
	int height;
	std::vector<Tile> field;
	Tile nullTile;
	*/
};

#endif /* MAP_TILEMAP_HPP_ */
