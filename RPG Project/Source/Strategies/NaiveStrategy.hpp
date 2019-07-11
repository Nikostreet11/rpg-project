/*
 * NaiveStrategy.hpp
 *
 *  Created on: Jul 6, 2019
 *      Author: nicop
 */

#ifndef STRATEGIES_NAIVESTRATEGY_HPP_
#define STRATEGIES_NAIVESTRATEGY_HPP_

#include "Strategy.hpp"

class NaiveStrategy:
		public Strategy
{
public:
	// Static constructor
    static std::shared_ptr<Strategy> getInstance();

	// Destructor
	virtual ~NaiveStrategy();

    // Deleted methods
    NaiveStrategy(std::shared_ptr<NaiveStrategy>) = delete;
    void operator=(std::shared_ptr<NaiveStrategy>)  = delete;

    // Functions
	virtual std::shared_ptr<Action> chooseAction(
			std::vector<std::shared_ptr<Action>> actions);

	virtual std::shared_ptr<Character> chooseTarget(
			std::vector<std::shared_ptr<Character>> allies,
			std::vector<std::shared_ptr<Character>> enemies);

protected:
	// Constructor
	NaiveStrategy();

private:
	// Static variables
	static std::shared_ptr<Strategy> INSTANCE;
};

#endif /* STRATEGIES_NAIVESTRATEGY_HPP_ */
