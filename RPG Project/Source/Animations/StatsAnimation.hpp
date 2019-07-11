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
			float delay,
			float duration,
			sf::Sprite& sprite,
			const sf::Texture* textureSheet,
			sf::Vector2u offset,
			sf::Vector2u size,
			sf::Vector2u spacing);
	virtual ~StatsAnimation();

	// Functions
	virtual void update(const float& dt, float modifier);
	virtual void render(sf::RenderTarget& target);

	void init(
			int value,
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
	void initColor();

	// Resources
	std::vector<sf::Sprite> digits;

	// Variables
	Stat stat;
	bool critical;
	bool healing;

	sf::Vector2u offset;
	sf::Vector2u size;
	sf::Vector2u spacing;
};

#endif /* ANIMATIONS_STATSANIMATION_HPP_ */
