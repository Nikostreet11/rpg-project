/*
 * DropDownList.hpp
 *
 *  Created on: May 15, 2019
 *      Author: nicop
 */

#ifndef GUI_DROPDOWNLIST_HPP_
#define GUI_DROPDOWNLIST_HPP_

#include "..\PCH\pch.hpp"

// Project
#include "Button.hpp"

namespace gui {

class DropDownList {
public:
	// Constructor / Destructor
	DropDownList(
			sf::Vector2f position,
			sf::Vector2f size,
			std::shared_ptr<sf::Font> font,
			std::vector<std::pair<std::string, std::string>> elements,
			const unsigned defaultIndex = 0);
	virtual ~DropDownList();

	// Functions
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);

	// Getters / Setters
	const std::string& getActiveKey() const;

private:
	// Resources
	std::shared_ptr<sf::Font> font;

	std::pair<std::string, std::unique_ptr<Button>> active;
	std::map<std::string, std::unique_ptr<Button>> elements;

	// Variables
	bool showList;
};

} /* namespace gui */

#endif /* GUI_DROPDOWNLIST_HPP_ */
