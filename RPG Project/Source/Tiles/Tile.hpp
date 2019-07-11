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
	enum Type
	{
		Invalid = -1,
		Default,
		Damaging,
		Dangerous,
		NumberOfTypes
	};

	enum Closeness
	{
		Background,
		Foreground
	};

	explicit Tile(
			sf::Vector2i index,
			float size,
			const sf::Texture& tileset,
			sf::Vector2u spriteIndex,
			unsigned spriteSize,
			Type type = Type::Default,
			Closeness closeness = Closeness::Foreground,
			bool crossable = true);
	virtual ~Tile();

	// Function
	void update();
	void render(
			sf::RenderTarget& target,
			const sf::RenderStates& states = sf::RenderStates::Default);

	const std::string getAsString() const;

	// Getters / Setters
	Type getType() const;
	Closeness getCloseness() const;
	bool isCrossable() const;
	const sf::Vector2f& getPosition() const;
	sf::Vector2f getSize() const;
	sf::FloatRect getGlobalBounds() const;
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
	Closeness closeness;
	bool crossable;

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
