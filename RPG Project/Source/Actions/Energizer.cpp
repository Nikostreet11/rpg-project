/*
 * Energizer.cpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#include "Energizer.hpp"

#include "..\Entities\Character.hpp"

Energizer::Energizer()
{
	staminaRestore = 20.f;
}

Energizer::~Energizer()
{
}

std::shared_ptr<ActionResults> Energizer::use(
		std::shared_ptr<Character> source,
		std::shared_ptr<Character> target)
{
	source->setState(Character::UsingObject);
	target->resetState();

	std::shared_ptr<ActionResults> results =
			std::make_shared<ActionResults>(source, target);

	// TODO: rework with other character stats, weapons and armor
	target->setStamina(target->getStamina() + staminaRestore);

	results->compute(source, target);

	target->playStatsAnimation(-std::round(staminaRestore), Stat::Stamina, false);

	return std::move(results);
}

