/*
 * DefensiveStrategy.hpp
 *
 *  Created on: Jul 11, 2019
 *      Author: nicop
 */

#ifndef STRATEGIES_DEFENSIVESTRATEGY_HPP_
#define STRATEGIES_DEFENSIVESTRATEGY_HPP_

#include "Strategy.hpp"

class DefensiveStrategy:
		public Strategy
{
public:
	// Static constructor
    static std::shared_ptr<Strategy> getInstance();

	// Destructor
	virtual ~DefensiveStrategy();

    // Deleted methods
	DefensiveStrategy(std::shared_ptr<DefensiveStrategy>) = delete;
    void operator=(std::shared_ptr<DefensiveStrategy>)  = delete;

    // Functions
	virtual std::shared_ptr<Action> chooseAction(
			std::vector<std::shared_ptr<Action>> actions);

	virtual std::shared_ptr<Character> chooseTarget(
			std::vector<std::shared_ptr<Character>> allies,
			std::vector<std::shared_ptr<Character>> enemies);

protected:
	// Constructor
	DefensiveStrategy();

private:
	// Static variables
	static std::shared_ptr<Strategy> INSTANCE;
};

#endif /* STRATEGIES_DEFENSIVESTRATEGY_HPP_ */
