/*
 * Angle.hpp
 *
 *  Created on: Apr 2, 2019
 *      Author: nicop
 */

#ifndef SOURCE_GRAPHICS_ANGLE_HPP_
#define SOURCE_GRAPHICS_ANGLE_HPP_

#include "../Exclude/Graphics/Icon.hpp"

namespace icons {

class Angle: public Icon {
public:
	Angle();
	virtual ~Angle();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//virtual void setSize(float size) override;

private:
	virtual void update();

	void loadVertexArray();

	sf::VertexArray vertexArray;
};

} /* namespace icons */

#endif /* SOURCE_GRAPHICS_ANGLE_HPP_ */
