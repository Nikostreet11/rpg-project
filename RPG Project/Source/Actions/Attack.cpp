/*
 * Attack.cpp
 *
 *  Created on: Jun 27, 2019
 *      Author: nicop
 */

#include "Attack.hpp"

#include "..\Entities\Character.hpp"

// Constructor / Destructor
Attack::Attack() :
		Action()
{
	staminaCost = 2.f;

	name = "Attack";
}

Attack::~Attack()
{
}

// Functions
std::shared_ptr<ActionResults> Attack::use(
		std::shared_ptr<Character> source,
		std::shared_ptr<Character> target)
{
	source->setState(Character::Attacking);
	target->setState(Character::Hit);

	std::shared_ptr<ActionResults> results =
			std::make_shared<ActionResults>(source, target);

	// TODO: rework with other character stats, weapons and armor
	Randomizer& r = Randomizer::getInstance();
	float damage = source->getStrenght() + r.getBetween(1, 5);

	bool critical = r.percentageOn(20.f);
	if (critical)
	{
		damage *= 1.5f;
	}

	source->setStamina(source->getStamina() - staminaCost);

	target->setHealth(target->getHealth() - damage);

	results->compute(source, target);

	target->playStatsAnimation(std::round(damage), Stat::Health, critical);

	return std::move(results);
}
