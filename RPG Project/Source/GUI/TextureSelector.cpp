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
		const sf::Texture& textureSheet)
{
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
}

TextureSelector::~TextureSelector()
{
	// TODO Auto-generated destructor stub
}

void TextureSelector::update()
{
}

void TextureSelector::render(std::shared_ptr<sf::RenderTarget> target)
{
	target->draw(bounds);
	target->draw(sheet);
}

} /* namespace gui */

