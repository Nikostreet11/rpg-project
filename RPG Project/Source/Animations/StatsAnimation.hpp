/*
 * StatsAnimation.hpp
 *
 *  Created on: Jul 3, 2019
 *      Author: nicop
 */

#ifndef ANIMATIONS_STATSANIMATION_HPP_
#define ANIMATIONS_STATSANIMATION_HPP_

#include "Animation.hpp"

#include "..\Stat.hpp"

class StatsAnimation:
		public Animation
{
public:
	// Constructor / Destructor
	explicit StatsAnimation(
			sf::Sprite& sprite,
			sf::Texture& textureSheet,
			float animationTimer,
			float delay,
			sf::Vector2u offset,
			sf::Vector2u size,
			sf::Vector2u spacing);
	virtual ~StatsAnimation();

	// Functions
	virtual void update(const float& dt, float modifier);
	virtual void render(sf::RenderTarget& target);

	void play(
			unsigned value,
			Stat stat = Health,
			bool critical = false);
	virtual void reset();
private:
	// Internal
	sf::Vector2u getIndex(char digit);

	// Initialization
	void initVariables();
	void initScale();
	void initPosition();
	void initColor(Stat stat, bool critical);

	// Resources
	std::vector<sf::Sprite> digits;

	// Variables

	Stat stat;
	bool critical;
};

#endif /* ANIMATIONS_STATSANIMATION_HPP_ */
