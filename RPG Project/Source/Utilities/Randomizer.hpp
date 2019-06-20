/*
 * Randomizer.h
 *
 *  Created on: Jul 13, 2018
 *      Author: Nikostreet11
 */

#ifndef UTILITIES_RANDOMIZER_HPP_
#define UTILITIES_RANDOMIZER_HPP_

class Randomizer
{
public:
	static Randomizer& getInstance();
	virtual ~Randomizer();

	float getBetween(int min, int max);
	bool percentageOn(float value);

protected:
	Randomizer();

	static Randomizer* instance;
};

#endif /* UTILITIES_RANDOMIZER_HPP_ */
