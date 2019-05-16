/*
 * DropDownList.hpp
 *
 *  Created on: May 15, 2019
 *      Author: nicop
 */

#ifndef RESOURCES_DROPDOWNLIST_HPP_
#define RESOURCES_DROPDOWNLIST_HPP_

// Project
#include "Button.hpp"

// Streams
#include <iostream>

// Time (legacy)
#include <ctime>

// General utilities (legacy)
#include <cstdlib>

// Smart pointers
#include <memory>

// SFML libraries
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

namespace gui {

class DropDownList {
public:
	// Contructor / Destructor
	DropDownList(
			std::shared_ptr<sf::Font> font,
			std::vector<std::string> list,
			const unsigned defaultIndex = 0);
	virtual ~DropDownList();

	// Functions
	void update(const sf::Vector2f& mousePos);
	void render(std::shared_ptr<sf::RenderTarget> target);

private:
	// Resources
	std::shared_ptr<sf::Font> font;
	std::unique_ptr<gui::Button> active;
	std::vector<std::unique_ptr<Button>> list;

	// Variables
	bool showList;
};

} /* namespace gui */

#endif /* RESOURCES_DROPDOWNLIST_HPP_ */
