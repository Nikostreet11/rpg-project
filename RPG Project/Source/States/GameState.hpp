/*
 * GameState.h
 *
 *  Created on: Apr 9, 2019
 *      Author: nicop
 */

#ifndef STATES_GAMESTATE_HPP_
#define STATES_GAMESTATE_HPP_

#include "State.hpp"

#include "../GUI/PauseMenu.hpp"

class GameState :
		public State
{
public:
	// Static functions

	// Constructors / Destructors
	explicit GameState(
			std::shared_ptr<sf::RenderWindow> window,
			std::shared_ptr<std::map<std::string, int>> supportedKeys,
			std::shared_ptr<std::stack<std::unique_ptr<State>>> states);
	virtual ~GameState();

	// Functions
	virtual void endState();

	virtual void update(const float& dt);
	virtual void updateInput(const float& dt);
	virtual void updatePlayerInput(const float& dt);
	virtual void updatePauseMenuButtons();
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
};

#endif /* STATES_GAMESTATE_HPP_ */
