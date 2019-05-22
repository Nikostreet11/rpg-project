/*
 * Exploration.h
 *
 *  Created on: Sep 19, 2018
 *      Author: nicop
 */

#ifndef STATES_EXPLORATION_H_
#define STATES_EXPLORATION_H_

#include "../Map/TileMap.hpp"
#include "../Party.h"
#include "State.hpp"

class Game;
class Exploration: public State {
public:
	// Static functions

	// Constructors / Destructors
	explicit Exploration(
			std::shared_ptr<sf::RenderWindow> window,
			std::shared_ptr<std::map<std::string, int>> supportedKeys,
			std::shared_ptr<std::stack<std::unique_ptr<State>>> states);
	virtual ~Exploration();

	// Functions
	virtual void endState();

	virtual void update(const float& dt);
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);

	//static Exploration* getInstance();

	virtual void draw();
	virtual void keyPressed_W(Game& game);
	virtual void keyPressed_A(Game& game);
	virtual void keyPressed_S(Game& game);
	virtual void keyPressed_D(Game& game);
	virtual void keyPressed_Enter(Game& game);

	const TileMap& getMap() const;
	const Party& getParty() const;

protected:
	// Initialization functions
	virtual void initKeybinds();

	//static Exploration* instance;

	void moveParty(Direction direction, Game& game);

	TileMap* map;
	Party party;
	//std::vector<Character*> npcs;
};

#endif /* STATES_EXPLORATION_H_ */
