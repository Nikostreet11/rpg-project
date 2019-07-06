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
			float delay,
			std::shared_ptr<Character> target);
	virtual ~AttackAnimation();
};

#endif /* ANIMATIONS_ATTACKANIMATION_HPP_ */
