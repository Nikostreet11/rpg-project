/*
 * DropDownList.cpp
 *
 *  Created on: May 15, 2019
 *      Author: nicop
 */

#include "../GUI/DropDownList.hpp"

namespace gui {

// Constructor / Destructor
DropDownList::DropDownList(
		sf::Vector2f position,
		sf::Vector2f size,
		std::shared_ptr<sf::Font> font,
		std::vector<std::pair<std::string, std::string>> elements,
		const unsigned defaultIndex) :
font(move(font)), showList(false)
{
	for (std::size_t index = 0; index < elements.size(); index++)
	{
		std::string& key = elements[index].first;
		std::string& text = elements[index].second;

		this->elements[key].reset(new Button(
				// Position
				sf::Vector2f(
						position.x,
						position.y + (index + 1) * size.y),
				// Size
				size,
				// Text options
				this->font, text, 40,
				sf::Color(220, 220, 220, 255),
				sf::Color(230, 230, 230, 255),
				sf::Color(210, 210, 210, 255),
				// Button colors
				sf::Color(140, 140, 140, 255),
				sf::Color(150, 150, 150, 255),
				sf::Color(130, 130, 130, 255),
				// Outline colors
				sf::Color(200, 200, 200, 0),
				sf::Color(250, 250, 250, 0),
				sf::Color(150, 150, 150, 0)
		));
	}

	active.first = elements[defaultIndex].first;
	active.second.reset(new Button(
			// Position
			position,
			// Size
			size,
			// Text options
			this->font, elements[defaultIndex].second, 40,
			sf::Color(240, 240, 240, 255),
			sf::Color(250, 250, 250, 255),
			sf::Color(230, 230, 230, 255),
			// Button colors
			sf::Color(160, 160, 160, 255),
			sf::Color(170, 170, 170, 255),
			sf::Color(150, 150, 150, 255),
			// Outline colors
			sf::Color(200, 200, 200, 255),
			sf::Color(250, 250, 250, 255),
			sf::Color(150, 150, 150, 255)
			));
	//active->setPosition(position);
}

DropDownList::~DropDownList()
{
}

// Functions
void DropDownList::update(const sf::Vector2f& mousePos)
{
	std::string& activeKey = active.first;
	Button& activeElement = *(active.second);

	activeElement.update(mousePos);

	if (activeElement.isPressed())
	{
		if (showList)
			showList = false;
		else
			showList = true;
	}

	if (showList)
	{
		for (auto &iterator : elements)
		{
			Button& element = *(iterator.second);

			element.update(mousePos);

			if (element.isPressed())
			{
				showList = false;
				activeKey = iterator.first;
				activeElement.setText(element.getText());
			}
		}
	}
}

void DropDownList::render(std::shared_ptr<sf::RenderTarget> target)
{
	Button& activeElement = *(active.second);

	activeElement.render(target);

	if (showList)
	{
		for (auto &iterator : elements)
		{
			gui::Button& element = *(iterator.second);

			element.render(target);
		}
	}
}

const std::string& DropDownList::getActiveKey() const
{
	return active.first;
}

} /* namespace gui */
