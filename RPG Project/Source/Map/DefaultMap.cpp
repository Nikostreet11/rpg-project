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
		std::map<std::string, std::shared_ptr<sf::Texture>> textures,
		std::shared_ptr<sf::Font> font) :
	TileMap(size, maxLayers, gridSize, tilesetName, spriteSize, textures, font)
{
}

DefaultMap::~DefaultMap()
{
}

std::vector<std::shared_ptr<Character>> DefaultMap::getFoes()
{
	Randomizer& rand = Randomizer::getInstance();

	unsigned numberOfEnemies =
			static_cast<unsigned>(std::round(rand.getBetween(2, 8)));

	std::vector<std::shared_ptr<Character>> foes;

	for (unsigned count = 0; count < numberOfEnemies; count++)
	{
		unsigned typeOfEnemy =
			static_cast<unsigned>(std::round(rand.getBetween(0, 8)));

		std::shared_ptr<Character> monster;

		switch (typeOfEnemy)
		{
		case 0:
			monster = std::make_shared<Monster>(
					Monster::Goblin,
					textures);
			break;

		case 1:
			monster = std::make_shared<Monster>(
					Monster::Wolf,
					textures);
			break;

		case 2:
			monster = std::make_shared<Monster>(
					Monster::Piranha,
					textures);
			break;

		case 3:
			monster = std::make_shared<Monster>(
					Monster::Skeleton,
					textures);
			break;

		case 4:
			monster = std::make_shared<Monster>(
					Monster::BlackWidow,
					textures);
			break;

		case 5:
			monster = std::make_shared<Monster>(
					Monster::GigasWorm,
					textures);
			break;

		case 6:
			monster = std::make_shared<Monster>(
					Monster::WargWolf,
					textures);
			break;

		case 7:
			monster = std::make_shared<Monster>(
					Monster::Werewolf,
					textures);
			break;

		case 8:
			monster = std::make_shared<Monster>(
					Monster::Zombie,
					textures);
			break;
		}

		monster->setStrategy(std::move(NaiveStrategy::getInstance()));
		foes.push_back(std::move(monster));
	}

	/*
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
	*/

	return foes;
}

sf::Vector2u DefaultMap::getBackground()
{
	return sf::Vector2u(0, 7);
}
