/*
 * AttackAnimation.cpp
 *
 *  Created on: Jul 6, 2019
 *      Author: nicop
 */

#include "AttackAnimation.hpp"

AttackAnimation::AttackAnimation(
		sf::Sprite& sprite,
		float animationTimer,
		float delay,
		std::shared_ptr<Character> target) :
	Animation(
			sprite,
			nullptr,
			animationTimer,
			std::vector<sf::Vector2u>(),
			sf::Vector2u(),
			sf::Vector2u(),
			sf::Vector2u())
{
}

AttackAnimation::~AttackAnimation()
{
}

