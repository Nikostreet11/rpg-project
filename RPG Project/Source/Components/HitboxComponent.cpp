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
void HitboxComponent::update()
{
	hitbox.setPosition(sprite.getPosition() + offset);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(hitbox);
}

bool HitboxComponent::intersect(const sf::FloatRect& rectangle)
{
	return hitbox.getGlobalBounds().intersects(rectangle);
}

const sf::Vector2f& HitboxComponent::getPosition() const
{
	return hitbox.getPosition();
}

void HitboxComponent::setPosition(const sf::Vector2f& position)
{
	hitbox.setPosition(position);
	sprite.setPosition(position - offset);
}

const sf::Vector2f& HitboxComponent::getSize() const
{
	return hitbox.getSize();
}

void HitboxComponent::setSize(const sf::Vector2f& size)
{
	hitbox.setSize(size);
}
