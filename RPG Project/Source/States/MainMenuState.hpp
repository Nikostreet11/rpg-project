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
	explicit MainMenuState(
			std::shared_ptr<sf::RenderWindow> window,
			std::shared_ptr<std::map<std::string, int>> supportedKeys,
			std::shared_ptr<std::stack<std::unique_ptr<State>>> states);
	virtual ~MainMenuState();

	// Functions
	virtual void endState();

	virtual void update(const float& dt);
	virtual void updateInput(const float& dt);
	void updateButtons();
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);
	void renderButtons(std::shared_ptr<sf::RenderTarget> target = nullptr);

	//static MainMenu* getInstance();

	/*virtual void draw();
	virtual void keyPressed_W(Game& game);
	virtual void keyPressed_A(Game& game);
	virtual void keyPressed_S(Game& game);
	virtual void keyPressed_D(Game& game);
	virtual void keyPressed_Enter(Game& game);*/

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
