/*
 * State.h
 *
 *  Created on: Sep 18, 2018
 *      Author: nicop
 */

#ifndef STATES_STATE_HPP_
#define STATES_STATE_HPP_

#include "..\Containers\StateData.hpp"
#include "..\Entities\Player.hpp"

// class Game;

class State
{
public:
	// Static functions

	// Constructor / Destructor
	State(StateData& stateData);
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

protected:
	// Initialization functions
	virtual void initKeybinds() = 0;

	// Structures
	struct Key {
		int code;
		bool wasPressed = false;
	};

	// Resources
	StateData& stateData;
	std::shared_ptr<GraphicsSettings> graphicsSettings;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<std::map<std::string, int>> supportedKeys;
	std::shared_ptr<std::stack<std::unique_ptr<State>>> states;
	std::map<std::string, Key> keybinds;
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;

	// Variables
	bool ended;
	bool paused;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

};

#endif /* STATES_STATE_HPP_ */
