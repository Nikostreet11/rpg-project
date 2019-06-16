/*
 * GraphicService.h
 *
 *  Created on: Sep 25, 2018
 *      Author: nicop
 */

#ifndef EXCLUDE_GRAPHICSERVICE_H_
#define EXCLUDE_GRAPHICSERVICE_H_

#include "States/Battle.h"
#include "States/Exploration.h"
#include "States/MainMenuState.hpp"

class GraphicService {
public:
	GraphicService();
	virtual ~GraphicService() = 0;

	virtual void drawMainMenu(MainMenuState* mainMenu) = 0;
	virtual void drawExploration(Exploration& exploration) = 0;
	virtual void drawBattle(Battle& battle) = 0;
};

#endif /* EXCLUDE_GRAPHICSERVICE_H_ */
