/*
 * Magic.hpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#ifndef ACTIONS_MAGIC_HPP_
#define ACTIONS_MAGIC_HPP_

#include "Action.hpp"

class Magic:
		public Action
{
public:
	// Functions
	virtual std::shared_ptr<ActionResults> use(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target) = 0;

protected:
	// Constructor / Destructor
	Magic();
	virtual ~Magic();

	// Initialization
	void initVariables();

	// Variables
	bool fireElement;
	bool iceElement;
	bool lightningElement;
};

#endif /* ACTIONS_MAGIC_HPP_ */
