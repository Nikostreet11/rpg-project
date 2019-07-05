/*
 * Action.hpp
 *
 *  Created on: Jun 27, 2019
 *      Author: nicop
 */

#ifndef ACTIONS_ACTION_HPP_
#define ACTIONS_ACTION_HPP_

#include "pch.hpp"

#include "..\Containers\ActionResults.hpp"
#include "..\Utilities\Randomizer.hpp"

#include "..\Stat.hpp"

// Forward declarations
class Character;

class Action
{
public:
	// Functions
	virtual std::shared_ptr<ActionResults> use(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target) = 0;

	// Getters / Setters
	const std::string& getName() const;
	bool isFriendly() const;

protected:
	// Constructor / Destructor
	Action();
	virtual ~Action();

	// Initialization
	void initVariables();

	// Variables
	std::string name;

	float healthCost;
	float manaCost;
	float staminaCost;

	bool friendly;
};

#endif /* ACTIONS_ACTION_HPP_ */
