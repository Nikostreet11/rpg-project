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
			sf::Sprite& sprite,
			float animationTimer,
			float delay);
	virtual ~AttackAnimation();

	// Functions
	virtual void update(const float& dt, float modifier);
	virtual void render(sf::RenderTarget& target);

	void play(std::shared_ptr<Character> target);
	virtual void reset();

protected:
	std::shared_ptr<Character> target;

	sf::Vector2f startingPosition;
};

#endif /* ANIMATIONS_ATTACKANIMATION_HPP_ */
