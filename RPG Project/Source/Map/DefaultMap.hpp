/*
 * DefaultMap.hpp
 *
 *  Created on: Jul 11, 2019
 *      Author: nicop
 */

#ifndef MAP_DEFAULTMAP_HPP_
#define MAP_DEFAULTMAP_HPP_

#include "TileMap.hpp"

class DefaultMap:
		public TileMap
{
public:
	// Constructor / Destructor
	explicit DefaultMap(
			sf::Vector2u size,
			unsigned maxLayers,
			float gridSize,
			const std::string& tilesetName,
			unsigned spriteSize,
			std::map<std::string, std::shared_ptr<sf::Texture>> textures,
			std::shared_ptr<sf::Font> font);
	virtual ~DefaultMap();

	virtual std::vector<std::shared_ptr<Character>> getFoes();
	virtual sf::Vector2u getBackground();
};

#endif /* MAP_DEFAULTMAP_HPP_ */
