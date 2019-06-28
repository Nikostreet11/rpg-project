/*
 * Monster.cpp
 *
 *  Created on: Jun 20, 2019
 *      Author: nicop
 */

#include "Monster.hpp"

Monster::Monster(
		Type type,
		const sf::Texture& spriteset,
		sf::Vector2f position,
		sf::Vector2f size) :
		Character()
{
	this->type = type;

	initVariables();
	initStats();
	initSprite(spriteset, position, size);
}

Monster::~Monster()
{
}

void Monster::update(const float& dt)
{
}

void Monster::initVariables()
{
	spriteOffset = {0, 0};
	spriteSize = {64, 64};
	spriteSpacing = {2, 2};

	switch (type)
	{
	case Goblin:
		spriteIndex = {0, 0};
		break;

	case Wolf:
		spriteIndex = {8, 0};
		break;

	case Piranha:
		spriteIndex = {9, 4};
		break;

	case Skeleton:
		spriteIndex = {7, 2};
		break;

	case BlackWidow:
		spriteIndex = {5, 4};
		break;

	case GigasWorm:
		spriteIndex = {9, 2};
		break;

	case WargWolf:
		spriteIndex = {4, 1};
		break;

	case Werewolf:
		spriteIndex = {9, 1};
		break;

	case Zombie:
		spriteIndex = {0, 1};
		break;

	default:
		spriteIndex = {0, 0};
		break;
	}
}

void Monster::initStats()
{
	switch (type)
	{
	case Goblin:
		name = "Goblin";
		break;

	case Wolf:
		name = "Wolf";
		break;

	case Piranha:
		name = "Piranha";
		break;

	case Skeleton:
		name = "Skeleton";
		break;

	case BlackWidow:
		name = "Black widow";
		break;

	case GigasWorm:
		name = "Gigas worm";
		break;

	case WargWolf:
		name = "Warg wolf";
		break;

	case Werewolf:
		name = "Werewolf";
		break;

	case Zombie:
		name = "Zombie";
		break;

	default:
		break;
	}
}
