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
			const sf::Texture* textureSheet,
			float delay,
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
	// Initialization
	void initVariables();

	// Resources
	sf::Sprite& sprite;
	const sf::Texture* textureSheet;
	std::vector<sf::Vector2u> indexVector;

	// Variables
	sf::Vector2u offset;
	sf::Vector2u size;
	sf::Vector2u spacing;
	unsigned currentIndex;

	bool started;
	bool done;

	float timer;
	float animationTimer;
	float delay;
	float delayTimer;
};

#endif /* ANIMATIONS_ANIMATION_HPP_ */
