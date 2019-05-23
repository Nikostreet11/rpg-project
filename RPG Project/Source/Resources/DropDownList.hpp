/*
 * DropDownList.hpp
 *
 *  Created on: May 15, 2019
 *      Author: nicop
 */

#ifndef RESOURCES_DROPDOWNLIST_HPP_
#define RESOURCES_DROPDOWNLIST_HPP_

#include "..\PCH\pch.hpp"

// Project
#include "Button.hpp"

namespace gui {

class DropDownList {
public:
	// Contructor / Destructor
	DropDownList(
			sf::Vector2f position,
			sf::Vector2f size,
			std::shared_ptr<sf::Font> font,
			std::vector<std::pair<std::string, std::string>> elements,
			const unsigned defaultIndex = 0);
	virtual ~DropDownList();

	// Functions
	void update(const sf::Vector2f& mousePos);
	void render(std::shared_ptr<sf::RenderTarget> target);

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

#endif /* RESOURCES_DROPDOWNLIST_HPP_ */
