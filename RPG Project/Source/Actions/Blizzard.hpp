/*
 * Blizzard.hpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#ifndef ACTIONS_BLIZZARD_HPP_
#define ACTIONS_BLIZZARD_HPP_

#include "Magic.hpp"

class Blizzard:
		public Magic
{
public:
	// Constructor / Destructor
	Blizzard();
	virtual ~Blizzard();

	// Functions
	virtual std::shared_ptr<ActionResults> use(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target);
};

#endif /* ACTIONS_BLIZZARD_HPP_ */
