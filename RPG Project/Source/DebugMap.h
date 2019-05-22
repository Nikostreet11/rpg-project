/*
 * DebugMap.h
 *
 *  Created on: Oct 5, 2018
 *      Author: nicop
 */

#ifndef SOURCE_DEBUGMAP_H_
#define SOURCE_DEBUGMAP_H_

#include "Map/TileMap.h"
#include "Party.h"
#include "States/Battle.h"

class DebugMap: public TileMap {
public:
	DebugMap(int width, int height);
	virtual ~DebugMap();

	virtual std::vector<Foe*> getFoes(Party& party);
	virtual Battle::Background getBackground();
};

#endif /* SOURCE_DEBUGMAP_H_ */
