/*
 * Ether.cpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#include "Ether.hpp"

#include "..\Entities\Character.hpp"

Ether::Ether()
{
	manaRestore = 20.f;
}

Ether::~Ether()
{
}

std::shared_ptr<ActionResults> Ether::use(
		std::shared_ptr<Character> source,
		std::shared_ptr<Character> target)
{
	source->setState(Character::UsingObject);
	target->resetState();

	std::shared_ptr<ActionResults> results =
			std::make_shared<ActionResults>(source, target);

	// TODO: rework with other character stats, weapons and armor
	target->setMana(target->getMana() + manaRestore);

	results->compute(source, target);

	target->playStatsAnimation(-std::round(manaRestore), Stat::Mana, false);

	return std::move(results);
}

