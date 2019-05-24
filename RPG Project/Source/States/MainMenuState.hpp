/*
 * MainMenu.h
 *
 *  Created on: Sep 19, 2018
 *      Author: nicop
 */

#ifndef STATES_MAINMENUSTATE_HPP_
#define STATES_MAINMENUSTATE_HPP_

#include "GameState.hpp"
#include "EditorState.hpp"
#include "SettingsState.hpp"
#include "../Resources/Button.hpp"

class MainMenuState:
		public State
{
public:
	// Static functions

	// Constructors / Destructors
	explicit MainMenuState(StateData& stateData);
	virtual ~MainMenuState();

	// Functions
	virtual void endState();

	virtual void update(const float& dt);
	virtual void updateInput(const float& dt);
	void updateButtons();
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);
	void renderButtons(std::shared_ptr<sf::RenderTarget> target = nullptr);

protected:
	// Initialization functions
	void initVariables();
	virtual void initKeybinds();
	void initFonts();
	void initBackground();
	void initButtons();

	// Variables
	sf::RectangleShape background;
	std::shared_ptr<sf::Font> font;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;

	// Resources
	sf::Texture backgroundTexture;

	//static MainMenu* instance;
};

#endif /* STATES_MAINMENUSTATE_HPP_ */
