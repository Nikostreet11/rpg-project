/*
 * Fire.hpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#ifndef ACTIONS_FIRE_HPP_
#define ACTIONS_FIRE_HPP_

#include "Magic.hpp"

class Fire:
		public Magic
{
public:
	// Constructor / Destructor
	Fire();
	virtual ~Fire();

	// Functions
	virtual std::shared_ptr<ActionResults> use(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target);
};

#endif /* ACTIONS_FIRE_HPP_ */
