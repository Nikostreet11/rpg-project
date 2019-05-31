/*
 * Button.hpp
 *
 *  Created on: Apr 22, 2019
 *      Author: nicop
 */

#ifndef GUI_BUTTON_HPP_
#define GUI_BUTTON_HPP_

#include "..\PCH\pch.hpp"

namespace gui {

class Button
{
public:
	// Enumerators
	enum class states {Idle, Hover, Active};

	// Constructor / Destructor
	explicit Button(
			sf::Vector2f position,
			sf::Vector2f size,
			std::shared_ptr<sf::Font> font,
			std::string text,
			unsigned characterSize,
			sf::Color textIdleColor,
			sf::Color textHoverColor,
			sf::Color textActiveColor,
			sf::Color fillIdleColor,
			sf::Color fillHoverColor,
			sf::Color fillActiveColor,
			sf::Color outlineIdleColor = sf::Color::Transparent,
			sf::Color outlineHoverColor = sf::Color::Transparent,
			sf::Color outlineActiveColor = sf::Color::Transparent);
	virtual ~Button();

	// Functions
	void update(const sf::Vector2f& mousePos);
	void render(std::shared_ptr<sf::RenderTarget> target);

	bool isPressed();
	bool isHold() const;
	bool isReleased();

	// Getters / Setters
	const std::string getText() const;
	void setText(const std::string& text);
	sf::FloatRect getGlobalBounds() const;

private:
	// Initialization
	void initVariables();

	// Resources
	std::shared_ptr<sf::Font> font;

	sf::RectangleShape shape;
	sf::Text text;

	// Variables
	Button::states state;
	bool pressEvent;
	bool releaseEvent;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color fillIdleColor;
	sf::Color fillHoverColor;
	sf::Color fillActiveColor;

	sf::Color outlineIdleColor;
	sf::Color outlineHoverColor;
	sf::Color outlineActiveColor;
};

} /* namespace gui */

#endif /* GUI_BUTTON_HPP_ */
