/*
 * EditorState.hpp
 *
 *  Created on: Apr 27, 2019
 *      Author: nicop
 */

#ifndef STATES_EDITORSTATE_HPP_
#define STATES_EDITORSTATE_HPP_

#include "State.hpp"

#include "../Resources/Button.hpp"
#include "..\GUI\PauseMenu.hpp"
#include "..\Map\TileMap.hpp"

class EditorState :
		public State
{
public:
	// Static functions

	// Constructors / Destructors
	explicit EditorState(
			std::shared_ptr<sf::RenderWindow> window,
			std::shared_ptr<std::map<std::string, int>> supportedKeys,
			std::shared_ptr<std::stack<std::unique_ptr<State>>> states);
	virtual ~EditorState();

	// Functions
	virtual void endState();

	virtual void update(const float& dt);
	virtual void updateInput(const float& dt);
	virtual void updateButtons();
	virtual void updatePauseMenu();
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);
	void renderButtons(std::shared_ptr<sf::RenderTarget> target = nullptr);

protected:
	// Initialization functions
	void initVariables();
	virtual void initKeybinds();
	void initFonts();
	void initBackground();
	void initPauseMenu();
	void initButtons();

	// Resources
	std::shared_ptr<sf::Font> font;
	std::unique_ptr<PauseMenu> pauseMenu;
	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
	TileMap map;

};

#endif /* STATES_EDITORSTATE_HPP_ */
