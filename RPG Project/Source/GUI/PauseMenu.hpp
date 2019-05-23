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
#include "../Resources/Button.hpp"
/*
// Utilities
#include <utility>
#include <thread>
#include <algorithm>

// Legacy
#include <cstdlib>
#include <ctime>
#include <cmath>

// Data structures
#include <set>
#include <list>
#include <deque>
#include <stack>
#include <vector>
#include <map>

// Smart Pointers
#include <memory>

// Data types
#include <string>

// Stream
#include <iostream>
#include <fstream>
#include <sstream>

// SFML
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
*/

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

	void update(const sf::Vector2f& mousePos);
	void render(std::shared_ptr<sf::RenderTarget> target);

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

#endif /* GUI_PAUSEMENU_HPP_ */
