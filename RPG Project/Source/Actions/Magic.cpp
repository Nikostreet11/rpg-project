/*
 * Magic.cpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#include "Magic.hpp"

#include "..\Entities\Character.hpp"

Magic::Magic(Type type)
{
	initVariables(type);
}

Magic::~Magic()
{
}

void Magic::initVariables(Type type)
{
	fireElement = false;
	iceElement = false;
	lightningElement = false;

	switch (type)
	{
	case Fire:
		name = "Fire";
		fireElement = true;
		manaCost = 3.f;
		break;

	case Blizzard:
		name = "Blizzard";
		iceElement = true;
		manaCost = 3.f;
		break;

	case Thunder:
		name = "Thunder";
		lightningElement = true;
		manaCost = 3.f;
		break;
	}
}

std::shared_ptr<ActionResults> Magic::use(
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

	bool critical =
			(fireElement && target->isWeakToFire())
			|| (iceElement && target->isWeakToIce())
			|| (lightningElement && target->isWeakToLightning());

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
