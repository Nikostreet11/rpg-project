/*
 * Selection.hpp
 *
 *  Created on: Mar 26, 2019
 *      Author: nicop
 */

#ifndef GUI_SELECTION_HPP_
#define GUI_SELECTION_HPP_

#include "pch.hpp"

#include "..\Direction.hpp"
#include "..\Icons\Caret.hpp"
#include "..\Icons\Angle.hpp"
//#include "../Exclude/Graphics/Angle.hpp"
//#include "../Exclude/Graphics/Caret.hpp"
//#include "../Exclude/MenuContainer.h"

namespace gui
{

class Selection
{
public:
	explicit Selection(
			sf::Vector2f position,
			sf::Vector2f size,
			sf::Vector2f offset,
			sf::Vector2u fieldSize,
			sf::Vector2u viewSize,
			unsigned textSize,
			std::shared_ptr<sf::Font> font);
	virtual ~Selection();

	// Functions
	void update();
	void render(sf::RenderTarget& target);
	void renderContainer(sf::RenderTarget& target);
	void renderEntries(sf::RenderTarget& target);
	void renderMarker(sf::RenderTarget& target);
	void renderScrolls(sf::RenderTarget& target);

	void moveMarker(Direction direction);
	void addEntry(std::string name);
	void removeEntry();

	// Getters / Setters
	const std::string getSelectedEntry() const;
	const size_t getIndex() const;
	//const sf::Vector2u& getMarkerIndex() const;
	//void setMarkerIndex(const sf::Vector2u& markerIndex);

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
	// Internal
	void updateEntriesPosition();

	// Initialization
	void initVariables();
	void initContainer();
	void initMarker();
	void initScrolls();

	// Resources
	sf::RectangleShape container;
	std::vector<sf::Text> entries;
	std::shared_ptr<sf::Font> font;
	//std::vector<std::string> entries;
	icons::Caret marker;

	icons::Angle leftScroll;
	icons::Angle topScroll;
	icons::Angle rightScroll;
	icons::Angle bottomScroll;

	// Variables
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Vector2f offset;
	sf::Vector2f spacing;
	float markerSpacing;
	float scrollsSize;
	//sf::Vector2f markerSpacing;

	sf::Vector2u fieldSize;
	sf::Vector2u viewIndex;
	sf::Vector2u viewSize;
	sf::Vector2u markerIndex;

	unsigned textSize;

	/*
	sf::Color textColor;
	sf::Color markerColor;
	sf::Color scrollsColor;

	float markerSize;
	float scrollsSize;
	*/
};

} /* namespace gui */

#endif /* GUI_SELECTION_HPP_ */
