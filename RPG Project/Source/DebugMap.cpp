/*
 * DebugMap.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: nicop
 */

#include "DebugMap.h"

#include "Randomizer.h"

#include "Tiletype.h"

DebugMap::DebugMap(int width, int height) : TileMap() {
	Randomizer& randomizer = Randomizer::getInstance();
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (randomizer.percentageOn(20)) {
				//setTile(x, y, Tile(TileType::bush));
			}
			else if (randomizer.percentageOn(5)) {
				//setTile(x, y-1, Tile(TileType::tree));
				//setTile(x, y, Tile(TileType::root));
			}
			else {
				//setTile(x, y, Tile(TileType::grass));
			}
		}
	}
}

DebugMap::~DebugMap() {}

std::vector<Foe*> DebugMap::getFoes(Party& party) {
	std::vector<Foe*> foeVector;
	foeVector.push_back(new Foe("Foe 1"));
	foeVector.push_back(new Foe("Foe 2"));
	foeVector.push_back(new Foe("Foe 3"));
	foeVector.push_back(new Foe("Foe 4"));
	foeVector.push_back(new Foe("Foe 5"));
	foeVector.push_back(new Foe("Foe 6"));
	foeVector.push_back(new Foe("Foe 7"));
	foeVector.push_back(new Foe("Foe 8"));
	return foeVector;
}

Battle::Background DebugMap::getBackground() {
	return Battle::Background::grassland;
}

