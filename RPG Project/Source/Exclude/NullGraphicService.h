/*
 * NullGraphicService.h
 *
 *  Created on: Sep 25, 2018
 *      Author: nicop
 */

#ifndef EXCLUDE_NULLGRAPHICSERVICE_H_
#define EXCLUDE_NULLGRAPHICSERVICE_H_

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Exclude/Camera.h"
#include "Exclude/GraphicsInfo.h"
#include "Exclude/GraphicService.h"
#include "Exclude/Randomizer.h"
#include "Exclude/SpriteInfo.h"
#include "States/Exploration.h"
#include "States/MainMenuState.hpp"

class NullGraphicService: public GraphicService {
public:
	NullGraphicService();
	virtual ~NullGraphicService();

	virtual void drawMainMenu(MainMenuState* mainMenu);
	virtual void drawExploration(Exploration& exploration);
	virtual void drawBattle(Battle& battle);
};

#endif /* EXCLUDE_NULLGRAPHICSERVICE_H_ */
