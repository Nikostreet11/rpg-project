/*
 * Map.h
 *
 *  Created on: Jul 23, 2018
 *      Author: nicop
 */

#ifndef MAP_H_
#define MAP_H_

#include "Foe.h"
#include "Party.h"

#include <string>
#include <vector>

#include "States/Battle.h"
#include "Tiles/Tile.hpp"

class Map {
public:
	virtual ~Map();

	/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
	 * Factory method														 *
	 * 																		 *
	 * Every specialization of Map defines what foes and how much of them	 *
	 * should the Party find when encountering a battle. The reference to	 *
	 * Party can be used to know where the party is, letting the concrete	 *
	 * Map decide which enemies to create.									 *
	 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
	virtual std::vector<Foe*> getFoes(Party& party) = 0;
	virtual Battle::Background getBackground() = 0;

	bool isOutOfBounds(int posX, int posY) const;
	const Tile& at(int x, int y);

	int getHeight() const;
	int getWidth() const;
	bool setTile(int x, int y, Tile tile);
	const Tile& getTile(int x, int y) const;

protected:
	Map(int width, int height);

	int width;
	int height;
	std::vector<Tile> field;
	Tile nullTile;
};

#endif /* MAP_H_ */
