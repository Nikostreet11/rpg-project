/*
 * Player.h
 *
 *  Created on: Jul 26, 2018
 *      Author: nicop
 */

#ifndef PARTY_H_
#define PARTY_H_

#include "Character.h"
#include "Human.h"

#include <vector>
#include <deque>
#include "directionsEnum.h"

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

#endif /* PARTY_H_ */
