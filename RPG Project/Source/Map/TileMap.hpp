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
	explicit TileMap();
	virtual ~TileMap();

	// Functions
	void update();
	void render(std::shared_ptr<sf::RenderTarget> target);

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
	// 3-dimensional vector
	std::vector< std::vector< std::vector<Tile> > > map;
	sf::Vector2u maxSize;
	unsigned maxLayers;
	unsigned gridSizeU;
	float gridSizeF;

	/*
	int width;
	int height;
	std::vector<Tile> field;
	Tile nullTile;
	*/
};

#endif /* MAP_TILEMAP_HPP_ */
