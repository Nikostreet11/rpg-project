/*
 * Selection.cpp
 *
 *  Created on: Mar 26, 2019
 *      Author: nicop
 */

#include "Selection.hpp"

namespace gui
{

Selection::Selection(
		sf::Vector2f position,
		sf::Vector2f size,
		sf::Vector2f offset,
		sf::Vector2u fieldSize,
		sf::Vector2u viewSize,
		unsigned textSize,
		std::shared_ptr<sf::Font> font) :
		font(std::move(font))/*,
textColor(sf::Color::Black),
markerColor(sf::Color::Black),
scrollsColor(sf::Color::Black),
textSize(30),
markerSize(20),
scrollsSize(20)*/
{
	this->position = position;
	this->size = size;
	this->offset = offset;
	this->fieldSize = fieldSize;
	this->viewSize = viewSize;
	this->textSize = textSize;

	initVariables();
	initContainer();
	initMarker();
	initScrolls();
}

Selection::~Selection() {}

/*
void Selection::onDraw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto text = texts.begin(); text != texts.end(); text++) {
		target.draw(*text, states);
	}

	if (markerIndex != sf::Vector2i(-1, -1))
		target.draw(marker, states);

}
*/

void Selection::update() {
/*
	if (viewSize.x > 1)
		spacing.x = (size.x - offset.x * 2) / viewSize.x;
	else
		spacing.x = 0;

	if (viewSize.y > 1)
		spacing.y = (size.y - offset.y * 2 - textSize) / (viewSize.y - 1);
	else
		spacing.y = 0;

	texts.clear();

	for (sf::Vector2i index(0, 0); index.y < viewSize.y; index.y++)
		for (index.x = 0; index.x < viewSize.x; index.x++) {

			std::size_t entriesIndex =
					(viewIndex.y + index.y) * fieldSize.x + viewIndex.x + index.x;

			if (entriesIndex < entries.size() &&
					viewIndex.x + index.x >= 0 &&
					viewIndex.y + index.y >= 0 &&
					viewIndex.x + index.x < fieldSize.x &&
					viewIndex.y + index.y < fieldSize.y) {

				sf::Text text;
				text.setFont(font);
				text.setCharacterSize(textSize);
				text.setFillColor(textColor);
				text.setPosition(sf::Vector2f(
						offset.x + index.x * spacing.x,
						offset.y + index.y * spacing.y));
				text.setString(entries.at(entriesIndex));
				texts.push_back(text);
			}
		}

	if (markerIndex != sf::Vector2i(-1, -1)) {
		marker.setSize(markerSize);
		marker.setColor(markerColor);
		marker.setPosition(sf::Vector2f(
				offset.x + markerIndex.x * spacing.x - marker.getSize(),
				offset.y + markerIndex.y * spacing.y + textSize - marker.getSize()));
	}
	*/
}

void Selection::render(sf::RenderTarget& target)
{
	renderContainer(target);
	renderEntries(target);
	renderMarker(target);
	renderScrolls(target);
}

void Selection::renderContainer(sf::RenderTarget& target)
{
	target.draw(container);
}

void Selection::renderEntries(sf::RenderTarget& target)
{
	for (unsigned y = 0; y < viewSize.y; y++)
	{
		for (unsigned x = 0; x < viewSize.x; x++)
		{
			std::size_t index =
					(viewIndex.y + y) * fieldSize.x + viewIndex.x + x;

			if (index < entries.size()
				/*&& viewIndex.x + xIndex >= 0
				&& viewIndex.y + yIndex >= 0
				&& viewIndex.x + xIndex < fieldSize.x
				&& viewIndex.y + yIndex < fieldSize.y*/)
			{
				target.draw(entries[index]);
			}
		}
	}
}

void Selection::renderMarker(sf::RenderTarget& target)
{
	if (entries.size() > 0)
	{
		marker.render(target);
	}
}

void Selection::renderScrolls(sf::RenderTarget& target)
{
	if (viewIndex.y > 0)
	{
		topScroll.render(target);
	}

	if (viewIndex.x > 0)
	{
		leftScroll.render(target);
	}

	if (viewIndex.y + viewSize.y < fieldSize.y
		&& entries.size() > fieldSize.x * viewSize.y)
	{
		bottomScroll.render(target);
	}

	if (viewIndex.x + viewSize.x < fieldSize.x
		&& entries.size() > viewSize.x)
	{
		rightScroll.render(target);
	}
}

void Selection::moveMarker(Direction direction)
{
	std::size_t index =
			(viewIndex.y + markerIndex.y) * fieldSize.x +
			viewIndex.x + markerIndex.x;

	switch (direction)
	{
	case Direction::Left:
		if (markerIndex.x > 0)
		{
			markerIndex.x--;
		}
		else if (viewIndex.x > 0)
		{
			viewIndex.x--;
		}
		break;

	case Direction::Up:
		if (markerIndex.y > 0)
		{
			markerIndex.y--;
		}
		else if (viewIndex.y > 0)
		{
			viewIndex.y--;
		}
		break;

	case Direction::Right:
		if (index + 1 < entries.size())
		{
			if (markerIndex.x < viewSize.x - 1)
			{
				markerIndex.x++;
			}
			else if (viewIndex.x + viewSize.x < fieldSize.x)
			{
				viewIndex.x++;
			}
		}
		break;

	case Direction::Down:
		if (index + fieldSize.x < entries.size())
		{
			if (markerIndex.y < viewSize.y - 1) {
				markerIndex.y++;
			}
			else if (viewIndex.y + viewSize.y < fieldSize.y)
			{
					viewIndex.y++;
			}
		}
		break;

	default:
		break;
	}

	marker.setPosition(
			position.x + offset.x + spacing.x * markerIndex.x,
			position.y + offset.y + spacing.y * markerIndex.y);

	updateEntriesPosition();
}

void Selection::addEntry(std::string name)
{
	sf::Text entry;
	entry.setFont(*font);
	entry.setCharacterSize(textSize);
	entry.setFillColor(sf::Color::White);
	entry.setString(name);
	/*
	entry.setPosition(
			position.x + offset.x + spacing.x * (entries.size() % fieldSize.x)
					+ markerSpacing,
			position.y + offset.y + spacing.y * (entries.size() / fieldSize.x)
					- textSize * 0.2f);
	*/
	entries.push_back(entry);
	updateEntriesPosition();
}

void Selection::removeEntry()
{
	if (entries.size() > 0)
	{
		entries.pop_back();
	}
}

// Getters / Setters
const std::string Selection::getSelectedEntry() const
{
	return entries[(viewIndex.y + markerIndex.y) * fieldSize.x
				   + viewIndex.x + markerIndex.x].getString();
}

/*
const sf::Vector2u& Selection::getMarkerIndex() const {
	return markerIndex;
}

void Selection::setMarkerIndex(const sf::Vector2u& markerIndex) {
	if (markerIndex.x < viewSize.x && markerIndex.y < viewSize.y) {
		this->markerIndex = markerIndex;
		update();
	}
}
*/

/*
void Selection::setEntries(const std::vector<std::string>& entries) {
	this->entries = entries;
	update();
}

const sf::Vector2i& Selection::getFieldSize() const {
	return fieldSize;
}

void Selection::setFieldSize(const sf::Vector2i& fieldSize) {
	this->fieldSize = fieldSize;
	update();
}

const sf::Vector2i& Selection::getViewIndex() const {
	return viewIndex;
}

void Selection::setViewIndex(const sf::Vector2i& viewIndex) {
	this->viewIndex = viewIndex;
	update();
}

const sf::Vector2i& Selection::getViewSize() const {
	return viewSize;
}

void Selection::setViewSize(const sf::Vector2i& viewSize) {
	this->viewSize = viewSize;
	update();
}*/

// Internal
void Selection::updateEntriesPosition()
{
	for (size_t y = 0; y < viewSize.y; y++)
	{
		for (size_t x = 0; x < viewSize.x; x++)
		{
			std::size_t index =
					(viewIndex.y + y) * fieldSize.x +
					viewIndex.x + x;

			if (index < entries.size())
			{
				entries[index].setPosition(
						position.x + offset.x + spacing.x * x
								/*+ markerSpacing*/,
						position.y + offset.y + spacing.y * y
								- textSize * 0.33f);

				if (x == markerIndex.x && y == markerIndex.y)
				{
					entries[index].move(markerSpacing, 0);
				}
			}
		}
	}
}

// Initialization
void Selection::initVariables()
{
	markerSpacing = textSize * 0.50f;

	scrollsSize = textSize * 0.8f;

	this->spacing = {
			(size.x - offset.x) / viewSize.x,
			(size.y - offset.y * 2 - textSize) / (viewSize.y - 1)};

	viewIndex = {0, 0};
	markerIndex = {0, 0};
}

void Selection::initContainer()
{
	container.setPosition(position);
	container.setSize(size);
	container.setFillColor(sf::Color::Blue);
	container.setOutlineThickness(-5);
	container.setOutlineColor(sf::Color::White);
}

void gui::Selection::initMarker()
{
	marker.setPosition(
			position.x + offset.x + spacing.x * markerIndex.x,
			position.y + offset.y + spacing.y * markerIndex.y);
	marker.setSize(textSize * 0.60f);
	marker.setColor(sf::Color::White);
}

void Selection::initScrolls()
{
	topScroll.setPosition(sf::Vector2f(
			position.x + size.x / 2 - scrollsSize / 2,
			position.y));
	topScroll.setSize(scrollsSize);
	topScroll.setColor(sf::Color::White);
	topScroll.setOrigin(sf::Vector2f(scrollsSize, 0));
	topScroll.setRotation(270);

	leftScroll.setPosition(sf::Vector2f(
			position.x,
			position.y + size.y / 2.f - scrollsSize / 2.f));
	leftScroll.setSize(scrollsSize);
	leftScroll.setColor(sf::Color::White);
	leftScroll.setOrigin(sf::Vector2f(scrollsSize, scrollsSize));
	leftScroll.setRotation(180);

	bottomScroll.setPosition(sf::Vector2f(
			position.x + size.x / 2 - scrollsSize / 2,
			position.y + size.y - scrollsSize));
	bottomScroll.setSize(scrollsSize);
	bottomScroll.setColor(sf::Color::White);
	bottomScroll.setOrigin(sf::Vector2f(0, scrollsSize));
	bottomScroll.setRotation(90);

	rightScroll.setPosition(sf::Vector2f(
			position.x + size.x - scrollsSize,
			position.y + size.y / 2 - scrollsSize / 2));
	rightScroll.setSize(scrollsSize);
	rightScroll.setColor(sf::Color::White);
	rightScroll.setOrigin(sf::Vector2f(0, 0));
	rightScroll.setRotation(0);
}

/*
const sf::Vector2f& Selection::getSize() const {
	return size;
}

void Selection::setSize(const sf::Vector2f& size) {
	this->size = size;
	update();
}

const sf::Vector2f& Selection::getOffset() const {
	return offset;
}

void Selection::setOffset(const sf::Vector2f& offset) {
	this->offset = offset;
	update();
}

sf::Color Selection::getTextColor() const {
	return textColor;
}

void Selection::setTextColor(sf::Color textColor) {
	this->textColor = textColor;
	update();
}

sf::Color Selection::getMarkerColor() const {
	return marker.getColor();
}

void Selection::setMarkerColor(sf::Color markerColor) {
	this->markerColor = markerColor;
	update();
}

sf::Color Selection::getScrollsColor() const {
	return scrollsColor;
}

void Selection::setScrollsColor(sf::Color scrollsColor) {
	this->scrollsColor = scrollsColor;
	update();
}

const sf::Font& Selection::getFont() const {
	return font;
}

void Selection::setFont(const sf::Font& font) {
	this->font = font;
	update();
}

int Selection::getTextSize() const {
	return textSize;
}

void Selection::setTextSize(int textSize) {
	this->textSize = textSize;
	update();
}
*/

} /* namespace gui */

const size_t gui::Selection::getIndex() const
{
	return (viewIndex.y + markerIndex.y) * fieldSize.x +
			viewIndex.x + markerIndex.x;
}
