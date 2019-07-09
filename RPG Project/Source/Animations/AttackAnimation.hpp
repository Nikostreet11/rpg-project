/*
 * AttackAnimation.hpp
 *
 *  Created on: Jul 6, 2019
 *      Author: nicop
 */

#ifndef ANIMATIONS_ATTACKANIMATION_HPP_
#define ANIMATIONS_ATTACKANIMATION_HPP_

#include "Animation.hpp"

class AttackAnimation:
		public Animation
{
public:
	AttackAnimation(
			float duration,
			sf::Sprite& sprite);
	virtual ~AttackAnimation();

	// Functions
	virtual void update(const float& dt, float modifier);
	virtual void render(sf::RenderTarget& target);

	void init(
			sf::Vector2f targetPosition,
			sf::Vector2f targetSize);

	virtual void reset();

protected:
	sf::Vector2f movementDistance;
	sf::Vector2f attackDistance;

	sf::Vector2f startingPosition;
	sf::Vector2f startingScale;
};

#endif /* ANIMATIONS_ATTACKANIMATION_HPP_ */
