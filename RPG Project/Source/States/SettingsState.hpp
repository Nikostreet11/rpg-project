/*
 * SettingsState.hpp
 *
 *  Created on: May 10, 2019
 *      Author: nicop
 */

#ifndef STATES_SETTINGSSTATE_HPP_
#define STATES_SETTINGSSTATE_HPP_

#include "State.hpp"

#include "../Resources/Button.hpp"
#include "../Resources/DropDownList.hpp"

class SettingsState :
	public State
{
public:
	// Static functions

	// Constructors / Destructors
	explicit SettingsState(
			std::shared_ptr<sf::RenderWindow> window,
			std::shared_ptr<std::map<std::string, int>> supportedKeys,
			std::shared_ptr<std::stack<std::unique_ptr<State>>> states);
	virtual ~SettingsState();

	// Functions
	virtual void endState();

	virtual void update(const float& dt);
	virtual void updateInput(const float& dt);
	void updateGUI(const float& dt);
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);
	void renderGUI(std::shared_ptr<sf::RenderTarget> target = nullptr);

protected:
	// Initialization functions
	void initVariables();
	virtual void initKeybinds();
	void initFonts();
	void initBackground();
	void initGUI();

	// Resources
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	std::shared_ptr<sf::Font> font;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
	std::map<std::string, std::unique_ptr<gui::DropDownList>> dropDownLists;
};

#endif /* STATES_SETTINGSSTATE_HPP_ */
