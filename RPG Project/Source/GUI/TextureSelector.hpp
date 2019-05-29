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
			const sf::Texture& textureSheet);
	virtual ~TextureSelector();

	// Functions
	void update();
	void render(std::shared_ptr<sf::RenderTarget> target);

private:
	// Resources
	sf::RectangleShape bounds;
	sf::Sprite sheet;
};

} /* namespace gui */

#endif /* GUI_TEXTURESELECTOR_HPP_ */
