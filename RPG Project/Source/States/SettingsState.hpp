/*
 * SettingsState.hpp
 *
 *  Created on: May 10, 2019
 *      Author: nicop
 */

#ifndef STATES_SETTINGSSTATE_HPP_
#define STATES_SETTINGSSTATE_HPP_

#include "../GUI/Button.hpp"
#include "../GUI/DropDownList.hpp"
#include "State.hpp"


class SettingsState :
	public State
{
public:
	// Static functions

	// Constructors / Destructors
	explicit SettingsState(StateData& stateData);
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
	virtual void initBindings();
	void initFonts();
	void initBackground();
	void initGUI();
	void initOptions();

	// Resources
	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	std::shared_ptr<sf::Font> font;
	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
	std::map<std::string, std::unique_ptr<gui::DropDownList>> dropDownLists;
	sf::Text options;
	std::vector<sf::VideoMode> videoModes;
};

#endif /* STATES_SETTINGSSTATE_HPP_ */
