/*
 * Selection.hpp
 *
 *  Created on: Mar 26, 2019
 *      Author: nicop
 */

#ifndef GUI_SELECTION_HPP_
#define GUI_SELECTION_HPP_

#include "pch.hpp"

#include "../Direction.hpp"
//#include "../Exclude/Graphics/Angle.hpp"
//#include "../Exclude/Graphics/Caret.hpp"
//#include "../Exclude/MenuContainer.h"

class Selection
{
public:
	Selection();
	virtual ~Selection();

	void update();
	void render(sf::RenderTarget& target);


	// data
	/*
	void setEntries(const std::vector<std::string>& entries);
	// logical
	const sf::Vector2i& getFieldSize() const;
	void setFieldSize(const sf::Vector2i& fieldSize);
	const sf::Vector2i& getViewIndex() const;
	void setViewIndex(const sf::Vector2i& viewIndex);
	const sf::Vector2i& getViewSize() const;
	void setViewSize(const sf::Vector2i& viewSize);
	*/
	const sf::Vector2i& getMarkerIndex() const;
	void setMarkerIndex(const sf::Vector2i& markerIndex);
	void moveMarkerIndex(Direction direction);
	// graphical
	/*
	const sf::Vector2f& getSize() const;
	void setSize(const sf::Vector2f& size);
	const sf::Vector2f& getOffset() const;
	void setOffset(const sf::Vector2f& offset);
	// colors
	sf::Color getTextColor() const;
	void setTextColor(sf::Color textColor);
	sf::Color getMarkerColor() const;
	void setMarkerColor(sf::Color markerColor);
	sf::Color getScrollsColor() const;
	void setScrollsColor(sf::Color scrollsColor);
	// preferences
	const sf::Font& getFont() const;
	void setFont(const sf::Font& font);
	int getTextSize() const;
	void setTextSize(int textSize);
	*/

private:
	// data
	//std::vector<std::string> entries;

	// logical
	sf::Vector2i fieldSize;
	sf::Vector2i viewIndex;
	sf::Vector2i viewSize;
	sf::Vector2i markerIndex;

	// graphic
	sf::Vector2f size;
	sf::Vector2f spacing;
	//sf::Vector2f markerSpacing;
	sf::Vector2f offset;

	// colors
	/*
	sf::Color textColor;
	sf::Color markerColor;
	sf::Color scrollsColor;
	*/

	// preferences
	sf::Font font;
	int textSize;
	float markerSize;
	float scrollsSize;

	// objects
	std::vector<sf::Text> entries;
	/*
	icons::Caret marker;
	icons::Angle leftScroll;
	icons::Angle topScroll;
	icons::Angle rightScroll;
	icons::Angle bottomScroll;
	*/
};

#endif /* GUI_SELECTION_HPP_ */
