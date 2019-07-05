/*
 * Ether.hpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#ifndef ACTIONS_ETHER_HPP_
#define ACTIONS_ETHER_HPP_

#include "Object.hpp"

class Ether:
		public Object
{
public:
	// Constructor / Destructor
	Ether();
	virtual ~Ether();

	// Functions
	virtual std::shared_ptr<ActionResults> use(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target);
};

#endif /* ACTIONS_ETHER_HPP_ */
