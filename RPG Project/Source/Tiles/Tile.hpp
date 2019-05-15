/*
 * Tile.h
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#ifndef TILES_TILE_HPP_
#define TILES_TILE_HPP_

#include "../Character.h"

#include "../TileType.h"

class Tile {
public:
	Tile();
	Tile(/*Texture texture, */TileType tileType);
	virtual ~Tile();

	virtual Tile& operator=(const Tile& right);

	//Texture getTexture() const;
	const TileType getTileType() const;
	bool isCrossable() const;
	bool isDangerous() const;

private:
	bool updateInfo(/*Texture texture, */TileType tileType);

	//Texture texture;
	TileType tileType;
	bool crossable;
	bool dangerous;
};

#endif /* TILES_TILE_HPP_ */
