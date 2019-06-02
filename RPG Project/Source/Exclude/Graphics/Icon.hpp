/*
 * Icon.hpp
 *
 *  Created on: Apr 2, 2019
 *      Author: nicop
 */

#ifndef SOURCE_GRAPHICS_ICON_HPP_
#define SOURCE_GRAPHICS_ICON_HPP_

#include <SFML/Graphics.hpp>

class Icon: public sf::Transformable, public sf::Drawable {
public:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

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

#endif /* SOURCE_GRAPHICS_ICON_HPP_ */
