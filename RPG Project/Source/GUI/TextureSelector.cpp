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
		const sf::Texture& textureSheet)
{
	active = false;
	this->gridSize = gridSize;

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
	if (bounds.getGlobalBounds().contains(
			static_cast<sf::Vector2f>(mousePosWindow)))
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

void TextureSelector::render(std::shared_ptr<sf::RenderTarget> target)
{
	target->draw(bounds);
	target->draw(sheet);

	if (active)
	{
		target->draw(selector);
	}
}

bool TextureSelector::getActive() const
{
	return active;
}

const sf::IntRect& TextureSelector::getTextureRect() const
{
	return textureRect;
}

} /* namespace gui */

