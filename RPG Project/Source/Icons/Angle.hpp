/*
 * Angle.hpp
 *
 *  Created on: Apr 2, 2019
 *      Author: nicop
 */

#ifndef ICONS_ANGLE_HPP_
#define ICONS_ANGLE_HPP_

#include "Icon.hpp"

namespace icons
{

class Angle:
		public Icon
{
public:
	Angle();
	virtual ~Angle();

	virtual void render(sf::RenderTarget& target);

	//virtual void setSize(float size) override;

private:
	virtual void update();

	void loadVertexArray();

	sf::VertexArray vertexArray;
};

} /* namespace icons */

#endif /* ICONS_ANGLE_HPP_ */
