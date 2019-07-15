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
#include "..\Entities\Monster.hpp"
#include "..\Entities\Human.hpp"
#include "Axis.hpp"

class TileMap
{
public:
	// Constructor / Destructor
	explicit TileMap(
			sf::Vector2u size,
			unsigned maxLayers,
			float gridSize,
			const std::string& tilesetName,
			unsigned spriteSize,
			std::map<std::string, std::shared_ptr<sf::Texture>> textures,
			std::shared_ptr<sf::Font> font);
	virtual ~TileMap();

	// Functions
	void update(sf::Vector2f mousePosView);
	void updateBoundsCollisions(
			std::shared_ptr<Entity> entity,
			const float& dt);
	void updateTilesCollisions(
			std::shared_ptr<Entity> entity,
			const float& dt);

	void render(
			sf::RenderTarget& target,
			Tile::Closeness closeness);

	void addTile(
			sf::Vector2u index,
			Tile::Type type,
			Tile::Closeness closeness,
			bool crossable);
	void addBaseTile(
			sf::Vector2u index,
			Tile::Type type,
			Tile::Closeness closeness,
			bool crossable);
	void removeTile(
			sf::Vector2u index);

	// Input / Output
	void saveToFile(const std::string& fileName);
	void loadFromFile(const std::string& fileName);

	// Getters / Setters
	bool isDangerousAt(sf::FloatRect rectangle);
	const sf::Texture& getTileset() const;
	bool isActive() const;
	void setEditorMode(bool editorMode);
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
	 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	virtual std::vector<std::shared_ptr<Character>> getFoes() = 0;

	/*virtual Battle::Background getBackground() = 0;

	const Tile& at(int x, int y);

	int getHeight() const;
	int getWidth() const;
	bool setTile(int x, int y, Tile tile);
	const Tile& getTile(int x, int y) const;
	*/

protected:
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;

private:
	// Internal
	void clear();
	void checkMaxValues();
	sf::Vector2u checkBounds(
			const sf::Vector2i& index);
	bool isOutOfBounds(
			sf::Vector2u index,
			Axis axis = Axis::NoAxis) const;

	// Initialization
	void initVariables();
	void initMap();
	void initTileset();
	void initBorder();
	void initCollisionBox();
	void initTilesCounter();

	// Resources
	std::vector< std::vector< std::unique_ptr<Tile> > > map;

	sf::Texture tileset;
	std::shared_ptr<sf::Font> font;
	//sf::IntRect tileRect;
	sf::RectangleShape border;
	sf::RectangleShape collisionBox;
	sf::Text tilesCounter;

	// Variables
	bool active;
	bool editorMode;

	//sf::Vector2f position;

	sf::Vector2u size;
	sf::Vector2u maxSize;
	//unsigned layers;
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
