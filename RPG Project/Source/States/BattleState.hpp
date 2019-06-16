/*
 * BattleState.hpp
 *
 *  Created on: Jun 16, 2019
 *      Author: Nikostreet11
 */

#ifndef STATES_BATTLESTATE_HPP_
#define STATES_BATTLESTATE_HPP_

#include "State.hpp"

class BattleState:
		public State
{
public:
	// Enumerators

	// Constructor / Destructor
	explicit BattleState(StateData& stateData);
	virtual ~BattleState();

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
	void initDeferredRendering();
	void initKeybinds();
	void initFonts();
	void initTextures();
	void initPlayers();
	//void initTileMap();
	void initPauseMenu();

	// Resources

	// Variables
};

#endif /* STATES_BATTLESTATE_HPP_ */
