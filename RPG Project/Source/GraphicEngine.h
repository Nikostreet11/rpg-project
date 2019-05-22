/*
 * GraphicEngine.h
 *
 *  Created on: Jul 25, 2018
 *      Author: nicop
 */

#ifndef GRAPHICENGINE_H_
#define GRAPHICENGINE_H_

#include "GraphicService.h"
#include "Camera.h"
#include "GraphicsInfo.h"
#include "SpriteInfo.h"
#include "Randomizer.h"

#include "CharacterBattleState.h"

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "Map/TileMap.h"
#include "States/Battle.h"
#include "States/Exploration.h"
#include "States/MainMenuState.hpp"
#include "Tiles/Tile.hpp"

class GraphicEngine : public GraphicService {
public:
	GraphicEngine(int resolutionX = 1024, int resolutionY = 576);
	virtual ~GraphicEngine();

	virtual void drawMainMenu(MainMenuState* mainMenu);
	virtual void drawExploration(Exploration& exploration);
	virtual void drawBattle(Battle& battle);

	sf::RenderWindow& getWindow();
	sf::Sprite& getSprite(Battle::Background background) const;
	sf::Sprite& getSprite(const Character& character) const;
	const sf::Font& getArial() const;

	Camera camera;

private:
	bool loadFonts();
	bool loadTextures();
	bool loadSpriteInfo(const Tile& tile);
	bool loadSpriteInfo(const BattleBackground& background);
	bool loadSpriteInfo(Character* character, const CharacterBattleState& state);
	void setSpritePosition(int& absolute, int relative, int step, int offset);
	void drawTile(int posX, int posY, const Tile& tile);
	void drawCharacter(Character* character);
	void drawBattleCharacter(int posX, int posY, Character* character);
	void drawSprite(int posX, int posY, int width, int height);
	void drawNullSprite(int posX, int posY, int width, int height);
	bool isVisible(int x, int y);

	int resolutionX;
	int resolutionY;

	int tileWidth;
	int tileHeight;
	int charWidth;
	int charHeight;

	sf::RenderWindow window;
	std::vector<GraphicsInfo*> graphics;
	SpriteInfo spriteInfo;
	sf::Font arial;

};

#endif /* GRAPHICENGINE_H_ */
