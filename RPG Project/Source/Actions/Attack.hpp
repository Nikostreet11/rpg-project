/*
 * Attack.hpp
 *
 *  Created on: Jun 27, 2019
 *      Author: nicop
 */

#ifndef ACTIONS_ATTACK_HPP_
#define ACTIONS_ATTACK_HPP_

#include "Action.hpp"

class Attack:
		public Action
{
public:
	Attack();
	virtual ~Attack();

	virtual std::shared_ptr<ActionResults> use(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target);
};

#endif /* ACTIONS_ATTACK_HPP_ */
