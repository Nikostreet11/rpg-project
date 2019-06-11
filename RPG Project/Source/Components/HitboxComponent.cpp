/*
 * HitboxComponent.cpp
 *
 *  Created on: May 3, 2019
 *      Author: nicop
 */

#include "HitboxComponent.hpp"

HitboxComponent::HitboxComponent(
		sf::Sprite& sprite,
		sf::Vector2f offset,
		sf::Vector2f size) :
sprite(sprite),
offset(offset)
{
	hitbox.setPosition(this->sprite.getPosition() + this->offset);
	hitbox.setSize(size);

	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(1.f);
	hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

// Functions
bool HitboxComponent::checkIntersect(const sf::FloatRect& rectangle)
{
	return hitbox.getGlobalBounds().intersects(rectangle);
}

void HitboxComponent::update()
{
	hitbox.setPosition(sprite.getPosition() + offset);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(hitbox);
}
