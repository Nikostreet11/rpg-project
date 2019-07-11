/*
 * AggressiveStrategy.hpp
 *
 *  Created on: Jul 11, 2019
 *      Author: nicop
 */

#ifndef STRATEGIES_AGGRESSIVESTRATEGY_HPP_
#define STRATEGIES_AGGRESSIVESTRATEGY_HPP_

#include "Strategy.hpp"

class AggressiveStrategy:
		public Strategy
{
public:
	// Static constructor
    static std::shared_ptr<Strategy> getInstance();

	// Destructor
	virtual ~AggressiveStrategy();

    // Deleted methods
	AggressiveStrategy(std::shared_ptr<AggressiveStrategy>) = delete;
    void operator=(std::shared_ptr<AggressiveStrategy>)  = delete;

    // Functions
	virtual std::shared_ptr<Action> chooseAction(
			std::vector<std::shared_ptr<Action>> actions);

	virtual std::shared_ptr<Character> chooseTarget(
			std::vector<std::shared_ptr<Character>> allies,
			std::vector<std::shared_ptr<Character>> enemies);

protected:
	// Constructor
	AggressiveStrategy();

private:
	// Static variables
	static std::shared_ptr<Strategy> INSTANCE;
};

#endif /* STRATEGIES_AGGRESSIVESTRATEGY_HPP_ */
