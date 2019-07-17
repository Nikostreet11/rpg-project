/*
 * GameState.h
 *
 *  Created on: Apr 9, 2019
 *      Author: nicop
 */

#ifndef STATES_EXPLORATIONSTATE_HPP_
#define STATES_EXPLORATIONSTATE_HPP_

#include "State.hpp"

#include "BattleState.hpp"

#include "..\GUI\PauseMenu.hpp"
#include "..\GUI\StatsMenu.hpp"
#include "..\Map\DefaultMap.hpp"
#include "..\Entities\Player.hpp"
#include "..\Entities\Human.hpp"
#include "..\Utilities\Randomizer.hpp"

class ExplorationState :
		public State
{
public:
	// Constructors / Destructors
	explicit ExplorationState(StateData& stateData);
	virtual ~ExplorationState();

	// Functions
	virtual void endState();

	virtual void update(const float& dt);
	virtual void updateCamera(const float& dt);
	virtual void updateInput(const float& dt);
	virtual void updatePlayerInput(const float& dt);
	virtual void updatePauseMenu();
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);

private:
	// Internal
	void checkForBattle(const float& dt);
	bool isGameOver();

	// Initialization functions
	void initVariables();
	void initDeferredRendering();
	void initCamera();
	void initBindings();
	void initFonts();
	void initTextures();
	void initParty();
	void initPlayers();
	void initTileMap();
	void initStatsMenu();
	void initPauseMenu();

	// Resources
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;
	std::shared_ptr<sf::View> camera;

	std::vector<std::shared_ptr<Character>> party;
	std::shared_ptr<Player> player;
	std::unique_ptr<TileMap> tileMap;

	std::shared_ptr<gui::StatsMenu> statsMenu;
	std::unique_ptr<gui::PauseMenu> pauseMenu;

	std::shared_ptr<sf::Font> font;

	// Variables
	float battleImmunityTimer;
	float battleImmunity;

};

#endif /* STATES_EXPLORATIONSTATE_HPP_ */
