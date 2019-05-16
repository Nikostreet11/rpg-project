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
		sf::Vector2f position,
		sf::Vector2f size,
		std::shared_ptr<sf::Font> font,
		std::vector<std::string> list,
		const unsigned defaultIndex) :
font(move(font)), showList(false)
{
	for (std::size_t index = 0; index < list.size(); index++)
	{
		std::unique_ptr<Button> buttonPtr(new Button(
				// Position
				sf::Vector2f(
						position.x,
						position.y + (index + 1) * size.y),
				// Size
				size,
				// Text options
				this->font, list[index], 50,
				sf::Color(230, 230, 230, 255),
				sf::Color(250, 250, 250, 255),
				sf::Color(210, 210, 210, 255),
				// Button colors
				sf::Color(150, 150, 150, 255),
				sf::Color(160, 160, 160, 255),
				sf::Color(140, 140, 140, 255)
				));

		this->list.push_back(std::move(buttonPtr));
	}

	active.reset(new Button(
			// Position
			position,
			// Size
			size,
			// Text options
			this->font, list[defaultIndex], 50,
			sf::Color(230, 230, 230, 255),
			sf::Color(250, 250, 250, 255),
			sf::Color(210, 210, 210, 255),
			// Button colors
			sf::Color(150, 150, 150, 255),
			sf::Color(160, 160, 160, 255),
			sf::Color(140, 140, 140, 255)
			));
	//active->setPosition(position);
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
