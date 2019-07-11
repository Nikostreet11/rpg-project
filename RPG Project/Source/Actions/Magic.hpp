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
	// Enumerators
	enum Type
	{
		Fire,
		Blizzard,
		Thunder
	};

	// Constructor / Destructor
	Magic(Type type);
	virtual ~Magic();

	// Functions
	virtual std::shared_ptr<ActionResults> use(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target);

protected:
	// Initialization
	void initVariables(Type type);

	// Variables
	bool fireElement;
	bool iceElement;
	bool lightningElement;
};

#endif /* ACTIONS_MAGIC_HPP_ */
