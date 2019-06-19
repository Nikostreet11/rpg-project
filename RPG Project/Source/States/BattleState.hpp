/*
 * BattleState.hpp
 *
 *  Created on: Jun 16, 2019
 *      Author: Nikostreet11
 */

#ifndef STATES_BATTLESTATE_HPP_
#define STATES_BATTLESTATE_HPP_

#include "State.hpp"

#include "..\GUI\PauseMenu.hpp"

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
	virtual void updatePauseMenu();
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);

	// Getters / Setters

private:
	// Initialization functions
	void initDeferredRendering();
	void initBindings();
	void initFonts();
	void initTextures();
	void initBackground();
	void initPauseMenu();

	// Resources
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;
	std::shared_ptr<sf::Font> font;
	sf::Sprite background;
	std::unique_ptr<gui::PauseMenu> pauseMenu;

	// Variables
};

#endif /* STATES_BATTLESTATE_HPP_ */
