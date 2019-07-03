/*
 * Animation.hpp
 *
 *  Created on: Jul 3, 2019
 *      Author: nicop
 */

#ifndef ANIMATIONS_ANIMATION_HPP_
#define ANIMATIONS_ANIMATION_HPP_

#include "pch.hpp"

class Animation
{
public:
	explicit Animation(
			sf::Sprite& sprite,
			std::shared_ptr<sf::Texture> textureSheet,
			float animationTimer,
			std::vector<sf::Vector2u> indexVector,
			sf::Vector2u offset,
			sf::Vector2u size,
			sf::Vector2u spacing);
	virtual ~Animation();

	// Functions
	virtual void play(const float& dt, float modifier);
	virtual void reset();

	// Getters / Setters
	bool isDone() const;

protected:
	// Resources
	sf::Sprite& sprite;
	std::shared_ptr<sf::Texture> textureSheet;
	std::vector<sf::Vector2u> indexVector;

	// Variables
	sf::Vector2u offset;
	sf::Vector2u size;
	sf::Vector2u spacing;
	unsigned currentIndex;
	float animationTimer;
	float timer;
	bool done;
};

#endif /* ANIMATIONS_ANIMATION_HPP_ */
