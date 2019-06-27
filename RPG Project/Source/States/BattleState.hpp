/*
 * BattleState.hpp
 *
 *  Created on: Jun 16, 2019
 *      Author: Nikostreet11
 */

#ifndef STATES_BATTLESTATE_HPP_
#define STATES_BATTLESTATE_HPP_

#include "State.hpp"

#include "..\Entities\Human.hpp"
#include "..\Entities\Monster.hpp"

#include "..\GUI\Dialogue.hpp"
#include "..\GUI\Selection.hpp"
#include "..\GUI\PauseMenu.hpp"
#include "..\Icons\Caret.hpp"

class BattleState:
		public State
{
public:
	// Enumerators
	enum Phase
	{
		InitialPhase,
		ActionSelect,
		TargetSelect,
		ActionResults,
		EndPhase
	};

	enum ActionMenu
	{
		Empty,
		MainActions,
		MagicMenu,
		ObjectMenu,
		TargetMenu
	};

	// Constructor / Destructor
	explicit BattleState(
			StateData& stateData/*,
			std::vector<std::shared_ptr<Character>> party,
			std::vector<std::shared_ptr<Character>> enemies*/);
	virtual ~BattleState();

	// Functions
	virtual void endState();

	virtual void update(const float& dt);
	virtual void updateInput(const float& dt);
	virtual void updateBattleInput(const float& dt);
	// virtual void updateDialogueMenu(const float& dt);
	virtual void updateActionMenu(const std::string& entry);
	virtual void updateActiveMarker();
	virtual void updatePauseMenu();
	virtual void render(
			std::shared_ptr<sf::RenderTarget> target = nullptr);
	virtual void renderCharacters(sf::RenderTarget& target);

	// Getters / Setters

private:
	// Internal
	void changePhase(Phase phase);
	void selectNextActive();

	// Initialization
	void initVariables();
	void initDeferredRendering();
	void initBindings();
	void initFonts();
	void initTextures();
	void initBackground();
	void initCharacters();
	void initActiveQueue();
	void initDialogueMenu();
	void initActionMenu(ActionMenu menu);
	void initPauseMenu();
	void initMarkers();

	// Resources
	std::vector<std::shared_ptr<Character>> party;
	std::vector<std::shared_ptr<Character>> enemies;
	std::vector<std::shared_ptr<Character>> activeQueue;
	std::vector<std::shared_ptr<Character>> targets;

	std::shared_ptr<Action> action;
	std::shared_ptr<Character> active;
	std::shared_ptr<Character> target;

	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;
	std::shared_ptr<sf::Font> font;
	sf::Sprite background;
	std::unique_ptr<gui::Dialogue> dialogueMenu;
	std::unique_ptr<gui::Selection> actionMenu;
	std::unique_ptr<gui::PauseMenu> pauseMenu;
	icons::Caret activeMarker;
	icons::Angle targetMarker;

	// Variables
	Phase phase;
	ActionMenu menu;
	size_t activeIndex;
};

#endif /* STATES_BATTLESTATE_HPP_ */
