/*
 * Potion.cpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#include "Potion.hpp"

#include "..\Entities\Character.hpp"

Potion::Potion()
{
	healthRestore = 50.f;
}

Potion::~Potion()
{
}

std::shared_ptr<ActionResults> Potion::use(
		std::shared_ptr<Character> source,
		std::shared_ptr<Character> target)
{
	source->setState(Character::UsingObject);
	target->resetState();

	std::shared_ptr<ActionResults> results =
			std::make_shared<ActionResults>(source, target);

	// TODO: rework with other character stats, weapons and armor
	target->setHealth(target->getHealth() + healthRestore);

	results->compute(source, target);

	target->playStatsAnimation(-std::round(healthRestore), Stat::Health, true);

	return std::move(results);
}

