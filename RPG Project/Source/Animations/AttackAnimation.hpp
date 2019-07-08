/*
 * AttackAnimation.hpp
 *
 *  Created on: Jul 6, 2019
 *      Author: nicop
 */

#ifndef ANIMATIONS_ATTACKANIMATION_HPP_
#define ANIMATIONS_ATTACKANIMATION_HPP_

#include "Animation.hpp"

#include "..\Entities\Character.hpp"

class AttackAnimation:
		public Animation
{
public:
	AttackAnimation(
			float duration,
			sf::Sprite& source);
	virtual ~AttackAnimation();

	// Functions
	virtual void update(const float& dt, float modifier);
	virtual void render(sf::RenderTarget& target);

	void init(
			sf::Vector2f targetPosition,
			sf::Vector2f targetSize);

	virtual void reset();

protected:
	// Initialization
	void initVariables();

	sf::Vector2f targetPosition;
	sf::Vector2f targetSize;

	sf::Vector2f startingPosition;
};

#endif /* ANIMATIONS_ATTACKANIMATION_HPP_ */
