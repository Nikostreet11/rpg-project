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
	virtual void updateInput(const float& dt);
	virtual void updatePlayerInput(const float& dt);
	virtual void updatePauseMenu();
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);

	// Getters / Setters

private:
	// Initialization functions
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPlayers();
	void initPauseMenu();

	// Resources
	std::unique_ptr<Player> player;
	std::unique_ptr<PauseMenu> pauseMenu;
	std::shared_ptr<sf::Font> font;
	TileMap map;

};

#endif /* STATES_GAMESTATE_HPP_ */
