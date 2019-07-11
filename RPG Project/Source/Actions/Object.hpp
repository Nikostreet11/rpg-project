/*
 * Object.hpp
 *
 *  Created on: Jul 5, 2019
 *      Author: nicop
 */

#ifndef ACTIONS_OBJECT_HPP_
#define ACTIONS_OBJECT_HPP_

#include "Action.hpp"

class Object:
		public Action
{
public:
	// Enumerators
	enum Type
	{
		Potion,
		Ether,
		Energizer
	};

	// Constructor / Destructor
	Object(Type type);
	virtual ~Object();

	// Functions
	virtual std::shared_ptr<ActionResults> use(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target);

protected:
	// Initialization
	void initVariables(Type type);

	// Variables
	float healthRestore;
	float manaRestore;
	float staminaRestore;
};

#endif /* ACTIONS_OBJECT_HPP_ */
