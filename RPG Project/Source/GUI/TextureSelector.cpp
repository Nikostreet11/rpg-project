/*
 * TextureSelector.cpp
 *
 *  Created on: May 29, 2019
 *      Author: nicop
 */

#include "TextureSelector.hpp"

namespace gui {

TextureSelector::TextureSelector(
		sf::Vector2f position,
		sf::Vector2f size,
		float gridSize,
		const sf::Texture& textureSheet,
		std::shared_ptr<sf::Font> font)
{
	active = false;
	this->gridSize = gridSize;
	hidden = true;

	hideButton.reset(new gui::Button(
			// Position
			position,
			// Size
			sf::Vector2f(100, 60),
			// Text options
			font, "Tile", 30,
			sf::Color(150, 150, 150, 250),
			sf::Color(250, 250, 250, 250),
			sf::Color(220, 220, 220, 250),
			// Button colors
			sf::Color(150, 150, 150, 0),
			sf::Color(250, 250, 250, 0),
			sf::Color(220, 220, 220, 0)
			));

	position.y += hideButton->getGlobalBounds().height;

	bounds.setPosition(position);
	bounds.setSize(size);
	bounds.setFillColor(sf::Color(50, 50, 50, 50));
	bounds.setOutlineThickness(1.f);
	bounds.setOutlineColor(sf::Color(200, 200, 200, 255));

	sheet.setTexture(textureSheet);
	sheet.setPosition(position);

	if (sheet.getGlobalBounds().width > bounds.getSize().x)
	{
		sheet.setTextureRect(sf::IntRect(
				0,
				0,
				bounds.getSize().x,
				sheet.getGlobalBounds().height));
	}

	if (sheet.getGlobalBounds().height > bounds.getSize().y)
	{
		sheet.setTextureRect(sf::IntRect(
				0,
				0,
				sheet.getGlobalBounds().width,
				bounds.getSize().y));
	}

	selector.setPosition(position);
	selector.setSize(sf::Vector2f(gridSize, gridSize));
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineThickness(1.f);
	selector.setOutlineColor(sf::Color::Yellow);

	textureRect.width = gridSize;
	textureRect.height = gridSize;
}

TextureSelector::~TextureSelector()
{
	// TODO Auto-generated destructor stub
}

void TextureSelector::update(sf::Vector2i mousePosWindow)
{
	hideButton->update(static_cast<sf::Vector2f>(mousePosWindow));

	if (hideButton->isPressed())
	{
		if (hidden)
		{
			hidden = false;
		}
		else
		{
			hidden = true;
		}
	}

	if (!hidden)
	{
		sf::Vector2f mousePosWindowF =
				static_cast<sf::Vector2f>(mousePosWindow);

		if (bounds.getGlobalBounds().contains(mousePosWindowF) ||
			hideButton->getGlobalBounds().contains(mousePosWindowF))
		{
			active = true;
		}
		else
		{
			active = false;
		}

		if (active)
		{
			mousePosGrid.x = static_cast<unsigned>(
					(mousePosWindow.x - bounds.getPosition().x) / gridSize);
			mousePosGrid.y = static_cast<unsigned>(
					(mousePosWindow.y - bounds.getPosition().y) / gridSize);

			selector.setPosition(sf::Vector2f(
					bounds.getPosition().x + mousePosGrid.x * gridSize,
					bounds.getPosition().y + mousePosGrid.y * gridSize));
		}

		textureRect.left = selector.getPosition().x - bounds.getPosition().x;
		textureRect.top = selector.getPosition().y - bounds.getPosition().y;
	}
}

void TextureSelector::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!hidden)
	{
		target->draw(bounds);
		target->draw(sheet);

		if (active)
		{
			target->draw(selector);
		}
	}

	hideButton->render(target);
}

bool TextureSelector::isActive() const
{
	return active;
}

const sf::IntRect& TextureSelector::getTextureRect() const
{
	return textureRect;
}

} /* namespace gui */

