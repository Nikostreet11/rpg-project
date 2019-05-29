/*
 * TextureSelector.hpp
 *
 *  Created on: May 29, 2019
 *      Author: nicop
 */

#ifndef GUI_TEXTURESELECTOR_HPP_
#define GUI_TEXTURESELECTOR_HPP_

#include "pch.hpp"

namespace gui {

class TextureSelector
{
public:
	TextureSelector(
			sf::Vector2f position,
			sf::Vector2f size,
			float gridSize,
			const sf::Texture& textureSheet);
	virtual ~TextureSelector();

	// Functions
	void update(sf::Vector2i mousePosWindow);
	void render(std::shared_ptr<sf::RenderTarget> target);

	// Getters / Setters
	bool getActive() const;

private:
	// Resources
	sf::RectangleShape bounds;
	sf::Sprite sheet;
	sf::RectangleShape selector;
	sf::Vector2u mousePosGrid;
	sf::IntRect textureRect;

	// Variables
	bool active;
	float gridSize;
};

} /* namespace gui */

#endif /* GUI_TEXTURESELECTOR_HPP_ */
