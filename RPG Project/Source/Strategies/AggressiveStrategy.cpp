/*
 * AggressiveStrategy.cpp
 *
 *  Created on: Jul 11, 2019
 *      Author: nicop
 */

#include "AggressiveStrategy.hpp"

#include "..\Actions\Action.hpp"
#include "..\Entities\Character.hpp"

std::shared_ptr<Strategy> AggressiveStrategy::INSTANCE = nullptr;

// Static constructor
std::shared_ptr<Strategy> AggressiveStrategy::getInstance()
{
	if (!INSTANCE)
	{
		INSTANCE = std::shared_ptr<Strategy>(new AggressiveStrategy());
	}

	return INSTANCE;
}

// Destructor
AggressiveStrategy::~AggressiveStrategy()
{
}

// Functions
std::shared_ptr<Action> AggressiveStrategy::chooseAction(
		std::vector<std::shared_ptr<Action>> actions)
{
	std::shared_ptr<Action> chosenAction;

	for (auto& action : actions)
	{
		if (action->getName() == "Attack")
		{
			chosenAction = action;
		}
	}

	return chosenAction;
}

std::shared_ptr<Character> AggressiveStrategy::chooseTarget(
		std::vector<std::shared_ptr<Character>> allies,
		std::vector<std::shared_ptr<Character>> enemies)
{
	std::shared_ptr<Character> target = nullptr;

	for (auto& enemy : enemies)
	{
		if (!target || enemy->getHealth() < target->getHealth())
		{
			target = enemy;
		}
	}

	return target;
}

// Constructor / Destructor
AggressiveStrategy::AggressiveStrategy()
{
}

