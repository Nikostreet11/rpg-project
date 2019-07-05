/*
 * Thunder.hpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#ifndef ACTIONS_THUNDER_HPP_
#define ACTIONS_THUNDER_HPP_

#include "Magic.hpp"

class Thunder:
		public Magic
{
public:
	// Constructor / Destructor
	Thunder();
	virtual ~Thunder();

	// Functions
	virtual std::shared_ptr<ActionResults> use(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target);
};

#endif /* ACTIONS_THUNDER_HPP_ */
