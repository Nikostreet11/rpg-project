/*
 * Tile.h
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#ifndef TILES_TILE_HPP_
#define TILES_TILE_HPP_

#include "pch.hpp"

class Tile {
public:
	Tile();
	Tile(sf::Vector2f position, float gridSizeF);
	virtual ~Tile();

	// Function
	void update();
	void render(std::shared_ptr<sf::RenderTarget> target);

	/*
	virtual Tile& operator=(const Tile& right);

	//Texture getTexture() const;
	const TileType getTileType() const;
	bool isCrossable() const;
	bool isDangerous() const;
	*/

protected:
	sf::RectangleShape shape;

private:
	/*
	bool updateInfo(Texture texture, TileType tileType);

	//Texture texture;
	TileType tileType;
	bool crossable;
	bool dangerous;
	*/
};

#endif /* TILES_TILE_HPP_ */
