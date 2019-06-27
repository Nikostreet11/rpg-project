/*
 * ActionResults.cpp
 *
 *  Created on: Jun 27, 2019
 *      Author: nicop
 */

#include "ActionResults.hpp"

#include "..\Entities\Character.hpp"

ActionResults::ActionResults(
		std::shared_ptr<Character> source,
		std::shared_ptr<Character> target)
{
	this->source.dHealth = source->getHealth();
	this->source.dMana = source->getMana();
	this->source.dStamina = source->getStamina();

	this->target.dHealth = target->getHealth();
	this->target.dMana = target->getMana();
	this->target.dStamina = target->getStamina();
}

ActionResults::~ActionResults()
{
}

void ActionResults::compute(
		std::shared_ptr<Character> source,
		std::shared_ptr<Character> target)
{
	this->source.dHealth -= source->getHealth();
	this->source.dMana -= source->getMana();
	this->source.dStamina -= source->getStamina();

	this->target.dHealth -= target->getHealth();
	this->target.dMana -= target->getMana();
	this->target.dStamina -= target->getStamina();
}
