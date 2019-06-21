/*
 * Icon.hpp
 *
 *  Created on: Apr 2, 2019
 *      Author: nicop
 */

#ifndef ICONS_ICON_HPP_
#define ICONS_ICON_HPP_

#include "pch.hpp"

class Icon:
		public sf::Transformable
{
public:
	virtual void render(sf::RenderTarget& target) = 0;

	float getSize() const;
	//void setSize(const sf::Vector2f& size);
	void setSize(float size);
	const sf::Color& getColor() const;
	void setColor(const sf::Color& color);

protected:
	Icon();
	virtual ~Icon();

	virtual void update() = 0;

	float size;
	sf::Color color;
};

#endif /* ICONS_ICON_HPP_ */
