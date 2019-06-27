/*
 * ActionResults.hpp
 *
 *  Created on: Jun 27, 2019
 *      Author: nicop
 */

#ifndef CONTAINERS_ACTIONRESULTS_HPP_
#define CONTAINERS_ACTIONRESULTS_HPP_

#include "pch.hpp"

class Character;

class ActionResults
{
public:
	// Structures
	struct CharacterData
	{
		float dHealth;
		float dMana;
		float dStamina;

		/*
		bool isPoisoned;
		bool isSleeping;
		bool isDead;
		*/
	};

	// Constructor / Destructor
	ActionResults(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target);
	virtual ~ActionResults();

	void compute(
			std::shared_ptr<Character> source,
			std::shared_ptr<Character> target);

	// Resources
	CharacterData source;
	CharacterData target;
};

#endif /* CONTAINERS_ACTIONRESULTS_HPP_ */
