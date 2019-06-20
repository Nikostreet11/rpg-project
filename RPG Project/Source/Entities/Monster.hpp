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
	// Enumerators
	enum Type
	{
		Goblin,
		Wolf,
		Piranha,
		Skeleton,
		BlackWidow,
		GigasWorm,
		WargWolf,
		Werewolf,
		Zombie
	};

	// Constructor / Destructor
	explicit Monster(
			sf::Vector2f position,
			sf::Vector2f size,
			const sf::Texture& spriteset,
			Type type);
	virtual ~Monster();

private:
	virtual void initVariables() override;

	Type type;
};

#endif /* ENTITIES_MONSTER_HPP_ */
