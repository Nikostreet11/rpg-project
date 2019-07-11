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
			bool repeated,
			float delay,
			float duration,
			sf::Sprite& sprite,
			const sf::Texture* textureSheet = nullptr);
	virtual ~Animation();

	// Functions
	virtual void update(const float& dt, float modifier) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

	virtual void play();
	virtual void pause();
	virtual void stop();

	virtual void reset() = 0;

	// Getters / Setters
	bool isDone() const;
	bool isStarted() const;

protected:
	// Initialization
	void initVariables();

	// Resources
	sf::Sprite& sprite;
	const sf::Texture* textureSheet;

	// Variables
	bool done;
	bool repeated;

	float timer;
	float duration;
	float delay;
	float delayTimer;
};

#endif /* ANIMATIONS_ANIMATION_HPP_ */
