/*
 * State.h
 *
 *  Created on: Sep 18, 2018
 *      Author: nicop
 */

#ifndef STATES_STATE_HPP_
#define STATES_STATE_HPP_

#include "../Entities/Player.hpp"

// class Game;

class State {
public:
	// Static functions

	// Constructors / Destructors
	explicit State(
			std::shared_ptr<sf::RenderWindow> window,
			std::shared_ptr<std::map<std::string, int>> supportedKeys,
			std::shared_ptr<std::stack<std::unique_ptr<State>>> states
			);
	virtual ~State() = 0;

	// Functions
	virtual void endState() = 0;
	virtual void pauseState();
	virtual void unpauseState();

	virtual void update(const float& dt) = 0;
	virtual void updateInput(const float& dt) = 0;
	virtual void updateMousePositions();
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr) = 0;

	// Getters / Setters
	const bool& isEnded() const;

	/*virtual void draw() = 0;
	virtual void keyPressed_W(Game& game) = 0;
	virtual void keyPressed_A(Game& game) = 0;
	virtual void keyPressed_S(Game& game) = 0;
	virtual void keyPressed_D(Game& game) = 0;
	virtual void keyPressed_Enter(Game& game) = 0;*/

protected:
	// Initialization functions
	virtual void initKeybinds() = 0;

	struct Key {
		int code;
		bool wasPressed = false;
	};

	// Resources
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<std::stack<std::unique_ptr<State>>> states;
	std::shared_ptr<std::map<std::string, int>> supportedKeys;
	std::map<std::string, Key> keybinds;
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;

	// Variables
	bool ended;
	bool paused;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

};

#endif /* STATES_STATE_HPP_ */
