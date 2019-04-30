/*
 * NullGraphicService.h
 *
 *  Created on: Sep 25, 2018
 *      Author: nicop
 */

#ifndef NULLGRAPHICSERVICE_H_
#define NULLGRAPHICSERVICE_H_

#include "GraphicService.h"

#include "GraphicsInfo.h"
#include "SpriteInfo.h"
#include "Randomizer.h"
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include "Camera.h"
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

#endif /* NULLGRAPHICSERVICE_H_ */
