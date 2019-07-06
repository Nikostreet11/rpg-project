/*
 * Strategy.hpp
 *
 *  Created on: Jul 6, 2019
 *      Author: nicop
 */

#ifndef STRATEGIES_STRATEGY_HPP_
#define STRATEGIES_STRATEGY_HPP_

#include "pch.hpp"

class Action;
class Character;

class Strategy
{
public:
	// Constructor / Destructor
	explicit Strategy();
	virtual ~Strategy() = 0;

	// Functions
	virtual std::shared_ptr<Action> chooseAction(
			std::vector<std::shared_ptr<Action>> actions) = 0;

	virtual std::shared_ptr<Character> chooseTarget(
			std::vector<std::shared_ptr<Character>> allies,
			std::vector<std::shared_ptr<Character>> enemies) = 0;
};

#endif /* STRATEGIES_STRATEGY_HPP_ */
