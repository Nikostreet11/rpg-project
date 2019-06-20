/*
 * Monster.hpp
 *
 *  Created on: Jun 20, 2019
 *      Author: nicop
 */

#ifndef ENTITIES_MONSTER_HPP_
#define ENTITIES_MONSTER_HPP_

#include "Character.hpp"

class Monster:
		public Character
{
public:
	explicit Monster(
			sf::Vector2f position,
			sf::Vector2f size,
			const sf::Texture& spriteset);
	virtual ~Monster();
};

#endif /* ENTITIES_MONSTER_HPP_ */
