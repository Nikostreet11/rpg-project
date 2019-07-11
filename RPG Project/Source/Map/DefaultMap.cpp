/*
 * DefaultMap.cpp
 *
 *  Created on: Jul 11, 2019
 *      Author: nicop
 */

#include "DefaultMap.hpp"

DefaultMap::DefaultMap(
		sf::Vector2u size,
		unsigned maxLayers,
		float gridSize,
		const std::string& tilesetName,
		unsigned spriteSize,
		std::map<std::string, std::shared_ptr<sf::Texture>> textures) :
	TileMap(size, maxLayers, gridSize, tilesetName, spriteSize, textures)
{
}

DefaultMap::~DefaultMap()
{
}

std::vector<std::shared_ptr<Character>> DefaultMap::getFoes()
{
	std::vector<std::shared_ptr<Character>> foes;

	for (unsigned index = 0; index < 2; index++)
	{
		std::shared_ptr<Character> monster =
				std::make_shared<Monster>(
						Monster::Werewolf,
						textures);

		monster->setStrategy(std::move(NaiveStrategy::getInstance()));

		foes.push_back(std::move(monster));
	}

	for (unsigned index = 0; index < 2; index++)
	{
		std::shared_ptr<Character> monster =
				std::make_shared<Monster>(
						Monster::GigasWorm,
						textures);

		monster->setStrategy(std::move(NaiveStrategy::getInstance()));

		foes.push_back(std::move(monster));
	}

	for (unsigned index = 0; index < 2; index++)
	{
		std::shared_ptr<Character> monster =
				std::make_shared<Monster>(
						Monster::Skeleton,
						textures);

		monster->setStrategy(std::move(NaiveStrategy::getInstance()));

		foes.push_back(std::move(monster));
	}

	for (unsigned index = 0; index < 2; index++)
	{
		std::shared_ptr<Character> monster =
				std::make_shared<Monster>(
						Monster::Zombie,
						textures);

		monster->setStrategy(std::move(NaiveStrategy::getInstance()));

		foes.push_back(std::move(monster));
	}

	return foes;
}
