/*
 * Blizzard.cpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#include "Blizzard.hpp"

#include "..\Entities\Character.hpp"

Blizzard::Blizzard()
{
	iceElement = true;

	manaCost = 3.f;
}

Blizzard::~Blizzard()
{
}

std::shared_ptr<ActionResults> Blizzard::use(
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

	bool critical = iceElement && target->isWeakToIce();

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

