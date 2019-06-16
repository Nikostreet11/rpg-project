/*
 * Player.h
 *
 *  Created on: Jul 26, 2018
 *      Author: nicop
 */

#ifndef EXCLUDE_PARTY_H_
#define EXCLUDE_PARTY_H_

#include <vector>
#include <deque>

#include "Exclude/Character.h"
#include "Exclude/directionsEnum.h"
#include "Exclude/Human.h"

class Party {
public:
	Party();
	virtual ~Party();

	/*void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();*/
	void move(Direction direction);

	//Human* getHero() const;
	Human* getHero(int position) const;
	bool addHero(Human* hero);
	bool removeHero();
	//bool removeHero(int position);
	int getSize() const;
	bool isEmpty() const;
	bool isFull() const;

	const int maxSize = 4;

private:
	void updateHeroesPosition();
	bool isOutOfBounds(int position) const;

	std::vector<Human*> heroes;
	std::vector<Direction> lastMovements;
};

#endif /* EXCLUDE_PARTY_H_ */
