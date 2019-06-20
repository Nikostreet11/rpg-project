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
		const sf::Texture& spriteset) :
		Character(position, size, spriteset)
{
	sprite.setTextureRect(sf::IntRect(264, 66, 64, 64));
	sprite.setScale(
			size.x / sprite.getTextureRect().width,
			size.y / sprite.getTextureRect().height);
}

Monster::~Monster()
{
}

