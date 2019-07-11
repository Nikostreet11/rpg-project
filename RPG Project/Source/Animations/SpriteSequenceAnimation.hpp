/*
 * SpriteSequenceAnimation.hpp
 *
 *  Created on: Jul 8, 2019
 *      Author: Nikostreet11
 */

#ifndef ANIMATIONS_SPRITESEQUENCEANIMATION_HPP_
#define ANIMATIONS_SPRITESEQUENCEANIMATION_HPP_

#include "Animation.hpp"

class SpriteSequenceAnimation:
		public Animation
{
public:
	// Constructor / Destructor
	explicit SpriteSequenceAnimation(
			bool repeated,
			float delay,
			float duration,
			sf::Sprite& sprite,
			const sf::Texture* textureSheet,
			std::vector<sf::Vector2u> indexVector,
			sf::Vector2u offset,
			sf::Vector2u size,
			sf::Vector2u spacing);
	virtual ~SpriteSequenceAnimation();

	// Functions
	virtual void update(const float& dt, float modifier);
	virtual void render(sf::RenderTarget& target);

	void init();

	virtual void reset();

protected:
	// Initialization
	void initVariables();

	// Resources
	std::vector<sf::Vector2u> indexVector;

	// Variables
	unsigned currentIndex;

	sf::Vector2u offset;
	sf::Vector2u size;
	sf::Vector2u spacing;
};

#endif /* ANIMATIONS_SPRITESEQUENCEANIMATION_HPP_ */
