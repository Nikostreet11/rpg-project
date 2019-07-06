/*
 * NaiveStrategy.hpp
 *
 *  Created on: Jul 6, 2019
 *      Author: nicop
 */

#ifndef STRATEGIES_NAIVESTRATEGY_HPP_
#define STRATEGIES_NAIVESTRATEGY_HPP_

#include "Strategy.hpp"

#include "..\Utilities\Randomizer.hpp"

class NaiveStrategy:
		public Strategy
{
public:
	// Constructor / Destructor
	NaiveStrategy();
	virtual ~NaiveStrategy();

	// Functions
	virtual std::shared_ptr<Action> chooseAction(
			std::vector<std::shared_ptr<Action>> actions);

	virtual std::shared_ptr<Character> chooseTarget(
			std::vector<std::shared_ptr<Character>> allies,
			std::vector<std::shared_ptr<Character>> enemies);
};

#endif /* STRATEGIES_NAIVESTRATEGY_HPP_ */
