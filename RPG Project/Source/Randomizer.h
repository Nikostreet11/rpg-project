/*
 * Randomizer.h
 *
 *  Created on: Jul 13, 2018
 *      Author: Nikostreet11
 */

#ifndef RANDOMIZER_H_
#define RANDOMIZER_H_

class Randomizer {
public:
	static Randomizer& getInstance();
	virtual ~Randomizer();

	float getBetween(int min, int max);
	bool percentageOn(float value);

protected:
	Randomizer();

	static Randomizer* instance;
};

#endif /* RANDOMIZER_H_ */