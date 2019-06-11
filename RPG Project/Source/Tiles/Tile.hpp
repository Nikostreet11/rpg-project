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
	enum Type {Invalid = -1, Default, Damaging, Dangerous, NumberOfTypes};

	Tile();
	explicit Tile(
			sf::Vector2i index,
			float size,
			const sf::Texture& tileset,
			sf::Vector2u spriteIndex,
			unsigned spriteSize,
			Type type = Type::Default,
			bool collision = false);
	virtual ~Tile();

	// Function
	void update();
	void render(
			sf::RenderTarget& target,
			const sf::RenderStates& states = sf::RenderStates::Default);

	const std::string getAsString() const;

	// Getters / Setters
	sf::Vector2u getSpriteIndex() const;
	sf::Vector2u getSpriteSize() const;
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
	sf::Sprite sprite;

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
