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
	if (instance == nullptr) {
		instance = new Randomizer();
	}
	return *instance;
}

float Randomizer::getBetween(int min, int max)
{
	double tmp1 = static_cast<double>(rand()) / RAND_MAX;

	double tmp2 = tmp1 * (max - min) + min;

	std::cout << "tmp1: " << tmp1 << std::endl;
	std::cout << "tmp2: " << tmp2 << std::endl;
	return tmp2;
}

bool Randomizer::percentageOn(float value) {
	std::cout << "Value: " << value << std::endl;
	if (value >= 100)
	{
		std::cout << std::endl;
		return true;
	}
	else
	{
		float testGetBetween = getBetween(0, 100);
		std::cout << std::endl;

		if (testGetBetween < value)
		{
			return true;
		}
		else
			return false;
	}
}

