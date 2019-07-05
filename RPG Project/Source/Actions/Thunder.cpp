/*
 * Thunder.cpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#include "Thunder.hpp"

#include "..\Entities\Character.hpp"

Thunder::Thunder()
{
	lightningElement = true;

	manaCost = 3.f;
}

Thunder::~Thunder()
{
}

std::shared_ptr<ActionResults> Thunder::use(
		std::shared_ptr<Character> source,
		std::shared_ptr<Character> target)
{
	source->setState(Character::CastingMagic);
	target->setState(Character::Hit);

	std::shared_ptr<ActionResults> results =
			std::make_shared<ActionResults>(source, target);

	// TODO: rework with other character stats, weapons and armor
	Randomizer& r = Randomizer::getInstance();

	float damage = source->getIntelligence() * r.getBetween(1, 5);

	bool critical = lightningElement && target->isWeakToLightning();

	if (critical)
	{
		damage *= 1.5f;
	}

	source->setMana(source->getMana() - manaCost);

	target->setHealth(target->getHealth() - damage);

	results->compute(source, target);

	target->playStatsAnimation(std::round(damage), Stat::Health, critical);

	return std::move(results);
}

