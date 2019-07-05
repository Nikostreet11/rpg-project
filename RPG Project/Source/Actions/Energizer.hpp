/*
 * Energizer.hpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#ifndef ACTIONS_ENERGIZER_HPP_
#define ACTIONS_ENERGIZER_HPP_

#include "Object.hpp"

class Energizer:
		public Object
{
public:
	// Constructor / Destructor
	Energizer();
	virtual ~Energizer();

	// Functions
	virtual std::shared_ptr<ActionResults> use(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target);
};

#endif /* ACTIONS_ENERGIZER_HPP_ */
