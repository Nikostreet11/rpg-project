/*
 * Potion.hpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#ifndef ACTIONS_POTION_HPP_
#define ACTIONS_POTION_HPP_

#include "Object.hpp"

class Potion:
		public Object
{
public:
	// Constructor / Destructor
	Potion();
	virtual ~Potion();

	// Functions
	virtual std::shared_ptr<ActionResults> use(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target);
};

#endif /* ACTIONS_POTION_HPP_ */
