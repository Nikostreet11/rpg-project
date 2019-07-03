/*
 * StatsAnimation.hpp
 *
 *  Created on: Jul 3, 2019
 *      Author: nicop
 */

#ifndef ANIMATIONS_STATSANIMATION_HPP_
#define ANIMATIONS_STATSANIMATION_HPP_

#include "Animation.hpp"

class StatsAnimation:
		public Animation
{
public:
	// Enumerators
	enum StatType
	{
		Health,
		Mana,
		Stamina
	};

	// Constructor / Destructor
	explicit StatsAnimation(
			sf::Sprite& sprite,
			sf::Texture& textureSheet,
			float animationTimer,
			sf::Vector2u offset,
			sf::Vector2u size,
			sf::Vector2u spacing,
			unsigned value,
			StatType statType = Health,
			bool critical = false);
	virtual ~StatsAnimation();

	// Functions
	virtual void play(const float& dt, float modifier);
	virtual void reset();

private:
	// Internal
	sf::Vector2u getIndex(unsigned digit);

	// Initialization
	void initVariables();
	void initPosition();
	void initScale();
	void initColor();

	// Resources
	std::vector<sf::Sprite> digits;

	// Variables
	StatType statType;
	bool critical;
};

#endif /* ANIMATIONS_STATSANIMATION_HPP_ */
