/*
 * Action.hpp
 *
 *  Created on: Jun 27, 2019
 *      Author: nicop
 */

#ifndef ACTIONS_ACTION_HPP_
#define ACTIONS_ACTION_HPP_

#include "pch.hpp"

// Forward declarations
class Character;

class Action
{
public:
	// Functions
	virtual void use(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target) = 0;

protected:
	// Constructor / Destructor
	Action();
	virtual ~Action();
};

#endif /* ACTIONS_ACTION_HPP_ */
