/*
 * Monster.cpp
 *
 *  Created on: Jun 20, 2019
 *      Author: nicop
 */

#include "Monster.hpp"

Monster::Monster(
		sf::Vector2f position,
		sf::Vector2f size,
		const sf::Texture& spriteset,
		Type type) :
		Character(position, size, spriteset)
{
	this->type = type;

	initVariables();
	initSprite(position, size, spriteset);
}

Monster::~Monster()
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

	case Type::Wolf:
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
