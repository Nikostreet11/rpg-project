/*
 * Caret.hpp
 *
 *  Created on: Apr 1, 2019
 *      Author: nicop
 */

#ifndef SOURCE_GRAPHICS_CARET_HPP_
#define SOURCE_GRAPHICS_CARET_HPP_

#include "Icon.hpp"

namespace icons {

class Caret: public Icon {
public:
	Caret();
	virtual ~Caret();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	//virtual void setSize(float size) override;

private:
	virtual void update();

	void loadVertexArray();

	sf::VertexArray vertexArray;
};

} /* namespace icons */

#endif /* SOURCE_GRAPHICS_CARET_HPP_ */
