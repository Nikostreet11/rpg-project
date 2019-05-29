/*
 * EditorState.hpp
 *
 *  Created on: Apr 27, 2019
 *      Author: nicop
 */

#ifndef STATES_EDITORSTATE_HPP_
#define STATES_EDITORSTATE_HPP_

#include "State.hpp"

#include "..\Resources\Button.hpp"
#include "..\GUI\PauseMenu.hpp"
#include "..\Map\TileMap.hpp"

class EditorState :
		public State
{
public:
	// Static functions

	// Constructor / Destructor
	explicit EditorState(StateData& stateData);
	virtual ~EditorState();

	// Functions
	virtual void endState();

	virtual void update(const float& dt);
	virtual void updateInput(const float& dt);
	virtual void updateEditorInput();
	virtual void updateGUI();
	virtual void updateButtons();
	virtual void updatePauseMenu();
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);
	virtual void renderGUI(std::shared_ptr<sf::RenderTarget> target = nullptr);
	virtual void renderButtons(std::shared_ptr<sf::RenderTarget> target = nullptr);

protected:
	// Initialization functions
	void initVariables();
	virtual void initKeybinds();
	void initFonts();
	void initBackground();
	void initTileMap();
	void initPauseMenu();
	void initGUI();
	void initButtons();

	// Resources
	std::shared_ptr<sf::Font> font;

	std::unique_ptr<TileMap> tileMap;
	std::unique_ptr<PauseMenu> pauseMenu;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
};

#endif /* STATES_EDITORSTATE_HPP_ */
