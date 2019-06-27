/*
 * Attack.cpp
 *
 *  Created on: Jun 27, 2019
 *      Author: nicop
 */

#include "Attack.hpp"

#include "..\Entities\Character.hpp"

Attack::Attack()
{
}

Attack::~Attack()
{
}

void Attack::use(
		std::shared_ptr<Character> source,
		std::shared_ptr<Character> target)
{
	// TODO: rework with other character stats, weapons and armor
	std::cout << "Target hp before the attack: " << target->getHealth() << std::endl;
	target->setHealth(target->getHealth() - source->getStrenght());
	std::cout << "Target hp after the attack: " << target->getHealth() << std::endl;
}
