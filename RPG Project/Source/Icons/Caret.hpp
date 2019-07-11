/*
 * Caret.hpp
 *
 *  Created on: Apr 1, 2019
 *      Author: nicop
 */

#ifndef ICONS_CARET_HPP_
#define ICONS_CARET_HPP_

#include "Icon.hpp"

namespace icons
{

class Caret:
		public Icon
{
public:
	Caret();
	virtual ~Caret();

	virtual void render(sf::RenderTarget& target);

	//virtual void setSize(float size) override;

private:
	virtual void update();

	void loadVertexArray();

	sf::VertexArray vertexArray;
};

} /* namespace icons */

#endif /* ICONS_CARET_HPP_ */
