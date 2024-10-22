/*
 * PauseMenu.hpp
 *
 *  Created on: May 9, 2019
 *      Author: nicop
 */

#ifndef GUI_PAUSEMENU_HPP_
#define GUI_PAUSEMENU_HPP_

#include "..\PCH\pch.hpp"

// Project
#include "Button.hpp"

namespace gui
{

class PauseMenu
{
public:
	// Constructor / Destructor
	PauseMenu(
			std::shared_ptr<sf::RenderWindow> window,
			std::shared_ptr<sf::Font> font);
	virtual ~PauseMenu();

	// Functions
	void addButton(
			const std::string key,
			float y,
			const std::string text);

	bool isButtonPressed(const std::string& key);

	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);

	// Getters / Setters
	std::map<std::string, std::unique_ptr<gui::Button>>& getButtons();

private:
	// Resources
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::shared_ptr<sf::Font> font;
	sf::Text menuText;

	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
};

} /* namespace gui */

#endif /* GUI_PAUSEMENU_HPP_ */
