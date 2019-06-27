/*
 * Attack.cpp
 *
 *  Created on: Jun 27, 2019
 *      Author: nicop
 */

#include "Attack.hpp"

#include "..\Entities\Character.hpp"

Attack::Attack() :
		Action()
{
	staminaCost = 2.f;
}

Attack::~Attack()
{
}

std::shared_ptr<ActionResults> Attack::use(
		std::shared_ptr<Character> source,
		std::shared_ptr<Character> target)
{
	std::shared_ptr<ActionResults> results =
			std::make_shared<ActionResults>(source, target);

	// TODO: rework with other character stats, weapons and armor
	Randomizer& r = Randomizer::getInstance();
	float damage = source->getStrenght() * r.getBetween(10, 20);

	source->setStamina(source->getStamina() - staminaCost);

	target->setHealth(target->getHealth() - damage);

	results->compute(source, target);

	return std::move(results);
}
