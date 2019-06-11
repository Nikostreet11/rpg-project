/*
 * GameState.h
 *
 *  Created on: Apr 9, 2019
 *      Author: nicop
 */

#ifndef STATES_GAMESTATE_HPP_
#define STATES_GAMESTATE_HPP_

#include "State.hpp"

#include "..\GUI\PauseMenu.hpp"
#include "..\Map\TileMap.hpp"
#include "..\Entities\Player.hpp"

class GameState :
		public State
{
public:
	// Static functions

	// Constructors / Destructors
	explicit GameState(StateData& stateData);
	virtual ~GameState();

	// Functions
	virtual void endState();

	virtual void update(const float& dt);
	virtual void updateCamera(const float& dt);
	virtual void updateInput(const float& dt);
	virtual void updatePlayerInput(const float& dt);
	virtual void updatePauseMenu();
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);

	// Getters / Setters

private:
	// Initialization functions
	void initDeferredRendering();
	void initCamera();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPlayers();
	void initTileMap();
	void initPauseMenu();

	// Resources
	std::shared_ptr<sf::View> camera;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;
	std::shared_ptr<Player> player;
	std::unique_ptr<TileMap> tileMap;
	std::unique_ptr<gui::PauseMenu> pauseMenu;

	std::shared_ptr<sf::Font> font;

};

#endif /* STATES_GAMESTATE_HPP_ */
