/*
 * Object.cpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#include "Object.hpp"

#include "..\Entities\Character.hpp"

Object::Object(Type type)
{
	initVariables(type);
}

Object::~Object()
{
}

std::shared_ptr<ActionResults> Object::use(
		std::shared_ptr<Character> source,
		std::shared_ptr<Character> target)
{
	source->setState(Character::UsingObject);
	if (source != target)
	{
		target->resetState();
	}

	std::shared_ptr<ActionResults> results =
			std::make_shared<ActionResults>(source, target);

	// TODO: rework with other character stats, weapons and armor
	target->setHealth(target->getHealth() + healthRestore);
	target->setMana(target->getMana() + manaRestore);
	target->setStamina(target->getStamina() + staminaRestore);

	results->compute(source, target);

	if (healthRestore > 0)
	{
		target->playStatsAnimation(-std::round(healthRestore), Stat::Health, true);
	}

	if (manaRestore > 0)
	{
		target->playStatsAnimation(-std::round(manaRestore), Stat::Mana, false);
	}

	if (staminaRestore > 0)
	{
		target->playStatsAnimation(-std::round(staminaRestore), Stat::Stamina, false);
	}

	return std::move(results);
}

void Object::initVariables(Type type)
{
	friendly = true;

	healthRestore = 0.f;
	manaRestore = 0.f;
	staminaRestore = 0.f;

	switch (type)
	{
	case Potion:
		name = "Potion";
		healthRestore = 50.f;
		break;

	case Ether:
		name = "Ether";
		manaRestore = 20.f;
		break;

	case Energizer:
		name = "Energizer";
		staminaRestore = 20.f;
		break;
	}
}

