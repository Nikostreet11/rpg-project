/*
 * TextureSelector.hpp
 *
 *  Created on: May 29, 2019
 *      Author: nicop
 */

#ifndef GUI_TEXTURESELECTOR_HPP_
#define GUI_TEXTURESELECTOR_HPP_

#include "pch.hpp"

#include "Button.hpp"

namespace gui {

class TextureSelector
{
public:
	TextureSelector(
			sf::Vector2f position,
			sf::Vector2f size,
			float gridSize,
			const sf::Texture& textureSheet,
			std::shared_ptr<sf::Font> font);
	virtual ~TextureSelector();

	// Functions
	void update(sf::Vector2i mousePosWindow);
	void render(sf::RenderTarget& target);

	// Getters / Setters
	bool isActive() const;
	const sf::IntRect& getTextureRect() const;

private:
	// Resources
	sf::RectangleShape bounds;
	sf::Sprite sheet;
	sf::RectangleShape selector;
	sf::Vector2u mousePosGrid;
	sf::IntRect textureRect;
	std::unique_ptr<gui::Button> hideButton;

	// Variables
	bool active;
	bool hidden;
	float gridSize;
};

} /* namespace gui */

#endif /* GUI_TEXTURESELECTOR_HPP_ */
