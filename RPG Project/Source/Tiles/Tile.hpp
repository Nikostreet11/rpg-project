/*
 * Tile.h
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#ifndef TILES_TILE_HPP_
#define TILES_TILE_HPP_

#include "pch.hpp"

class Tile
{
public:
	enum Type {Default = 0, Damaging};

	Tile();
	explicit Tile(
			sf::Vector2f position,
			float gridSize,
			const sf::Texture& tileTextureSheet,
			sf::IntRect textureRect,
			Type type = Type::Default,
			bool collision = false);
	virtual ~Tile();

	// Function
	void update();
	void render(std::shared_ptr<sf::RenderTarget> target);

	const std::string getAsString() const;

	// Getters / Setters
	const sf::IntRect& getTextureRect() const;
	/*
	virtual Tile& operator=(const Tile& right);

	//Texture getTexture() const;
	const TileType getTileType() const;
	bool isCrossable() const;
	bool isDangerous() const;
	*/

protected:
	// Resources
	sf::RectangleShape shape;

	// Variables
	Type type;
	bool collision;

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
