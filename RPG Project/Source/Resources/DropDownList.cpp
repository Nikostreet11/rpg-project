/*
 * DropDownList.cpp
 *
 *  Created on: May 15, 2019
 *      Author: nicop
 */

#include "DropDownList.hpp"

namespace gui {

// Constructor / Destructor
DropDownList::DropDownList(
		std::shared_ptr<sf::Font> font,
		std::vector<std::string> list,
		const unsigned defaultIndex) :
font(move(font)), showList(false)
{
	for (std::size_t index; index < list.size(); ++index)
	{
		std::unique_ptr<Button> buttonPtr(new Button(
				// Position
				sf::Vector2f(100, 100),
				// Size
				sf::Vector2f(400, 100),
				// Text options
				this->font, list[index], 50,
				sf::Color(150, 150, 150, 250),
				sf::Color(250, 250, 250, 250),
				sf::Color(220, 220, 220, 250),
				// Button colors
				sf::Color(150, 150, 150, 0),
				sf::Color(250, 250, 250, 0),
				sf::Color(220, 220, 220, 0)
				));

		this->list.push_back(std::move(buttonPtr));
	}

	active.reset(new Button(*this->list[defaultIndex]));
}

DropDownList::~DropDownList()
{
}

// Functions
void DropDownList::update(const sf::Vector2f& mousePos)
{
	active->update(mousePos);

	if (active->isPressed())
	{
		if (showList)
			showList = false;
		else
			showList = true;
	}

	if (showList)
	{
		for (auto &iterator : list)
		{
			iterator->update(mousePos);
		}
	}
}

void DropDownList::render(std::shared_ptr<sf::RenderTarget> target)
{
	active->render(target);

	if (showList)
	{
		for (auto &iterator : list)
		{
			iterator->render(target);
		}
	}
}

} /* namespace gui */
