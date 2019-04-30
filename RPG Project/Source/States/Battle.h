/*
 * Battle.h
 *
 *  Created on: Sep 19, 2018
 *      Author: nicop
 */

#ifndef STATES_BATTLE_H_
#define STATES_BATTLE_H_

#include "../Menu.h"
#include "../Party.h"
#include "../Foe.h"
#include "../MenuContainer.h"

#include "../graphics/InnerWindow.hpp"
#include "../graphics/Selection.hpp"

#include "../BattleState.h"
#include "../BattleBackground.h"

#include <vector>
#include "State.hpp"

class GraphicEngine;
class Battle: public State {
public:
	enum class SubState {
		start,
		player_select_action/*,
		player_select_target,
		player_action_result,
		computer_action_result,
		won,
		lost,
		fled,
		none*/
	};

	enum class Background {
		grassland/*, desert, deck, cave_A, cave_B, watercave_A, watercave_B, coast, palace,
		darkForest, basement_A, basement_B, lavacave, forest_A, forest_B, forest_C, river,
		waterfall, lake, swamp_A, swamp_B, castle_A, castle_B*/, none};

	explicit Battle(
			std::shared_ptr<sf::RenderWindow> window,
			std::shared_ptr<std::map<std::string, int>> supportedKeys,
			std::shared_ptr<std::stack<std::unique_ptr<State>>> states);
	virtual ~Battle();

	// Functions
	virtual void endState();

	virtual void update(const float& dt);
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);

	//static Battle* getInstance();

	virtual void draw();
	void draw_start(GraphicEngine& graphicEngine);
	void draw_player_select_action(GraphicEngine& graphicEngine);

	virtual void keyPressed_W(Game& game);
	virtual void keyPressed_A(Game& game);
	virtual void keyPressed_S(Game& game);
	virtual void keyPressed_D(Game& game);
	virtual void keyPressed_Enter(Game& game);

	const std::vector<Character*>& getParty() const;
	void setParty(std::vector<Character*> party);
	const std::vector<Foe*>& getFoes() const;
	void setFoes(std::vector<Foe*> foes);
	Background getBackground() const;
	void setBackground(Background background);
	const MenuContainer& getMenu() const;
	SubState getState() const;
	void setState(SubState state);

protected:
	// Initialization functions
	virtual void initKeybinds();

	//static Battle* instance;

	SubState state;
	Background background;

	void loadMenu();
	void loadGraphics();

	//StateEnum state;

	std::vector<Character*> party;
	std::vector<Foe*> foes;

	MenuContainer menu;

	InnerWindow commandWindow;
	Selection commands;
	//BattleState state;
	//BattleBackground background;
};

#endif /* STATES_BATTLE_H_ */
