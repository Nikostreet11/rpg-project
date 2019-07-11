/*
 * DefensiveStrategy.cpp
 *
 *  Created on: Jul 11, 2019
 *      Author: nicop
 */

#include "DefensiveStrategy.hpp"

#include "..\Actions\Action.hpp"
#include "..\Entities\Character.hpp"

std::shared_ptr<Strategy> DefensiveStrategy::INSTANCE = nullptr;

// Static constructor
std::shared_ptr<Strategy> DefensiveStrategy::getInstance()
{
	if (!INSTANCE)
	{
		INSTANCE = std::shared_ptr<Strategy>(new DefensiveStrategy());
	}

	return INSTANCE;
}

// Destructor
DefensiveStrategy::~DefensiveStrategy()
{
}

// Functions
std::shared_ptr<Action> DefensiveStrategy::chooseAction(
		std::vector<std::shared_ptr<Action>> actions)
{
	std::shared_ptr<Action> chosenAction;

	for (auto& action : actions)
	{
		if (action->getName() == "Potion")
		{
			chosenAction = action;
		}
	}

	return chosenAction;
}

std::shared_ptr<Character> DefensiveStrategy::chooseTarget(
		std::vector<std::shared_ptr<Character>> allies,
		std::vector<std::shared_ptr<Character>> enemies)
{
	std::shared_ptr<Character> target = nullptr;

	for (auto& ally : allies)
	{
		if (!target || ally->getHealth() < target->getHealth())
		{
			target = ally;
		}
	}

	return target;
}

// Constructor / Destructor
DefensiveStrategy::DefensiveStrategy()
{
}
