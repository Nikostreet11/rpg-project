/*
 * Randomizer.cpp
 *
 *  Created on: Jul 13, 2018
 *      Author: Nikostreet11
 */

#include "Randomizer.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

Randomizer* Randomizer::instance = nullptr;

Randomizer::Randomizer() {
	srand(time(0));
}

Randomizer::~Randomizer() {
	instance = nullptr;
}

Randomizer& Randomizer::getInstance() {
	if (instance == nullptr)
	{
		instance = new Randomizer();
	}
	return *instance;
}

float Randomizer::getBetween(int min, int max)
{
	return static_cast<double>(rand()) / RAND_MAX * (max - min) + min;
}

bool Randomizer::percentageOn(float value)
{
	if (value >= 100)
	{
		std::cout << std::endl;
		return true;
	}
	else
	{
		float testGetBetween = getBetween(0, 100);

		if (testGetBetween < value)
		{
			return true;
		}
		else
			return false;
	}
}

