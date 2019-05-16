/*
 * Button.hpp
 *
 *  Created on: Apr 22, 2019
 *      Author: nicop
 */

#ifndef RESOURCES_BUTTON_HPP_
#define RESOURCES_BUTTON_HPP_

// Streams
#include <iostream>

// Time (legacy)
#include <ctime>

// General utilities (legacy)
#include <cstdlib>

// Smart pointers
#include <memory>

// SFML libraries
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

namespace gui {

class Button
{
public:
	// Enumerators
	enum class states {Idle, Hover, Active};

	// Constructors / Destructors
	explicit Button(
			sf::Vector2f position,
			sf::Vector2f size,
			std::shared_ptr<sf::Font> font,
			std::string text,
			unsigned characterSize,
			sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	// Functions
	void update(const sf::Vector2f& mousePos);
	void render(std::shared_ptr<sf::RenderTarget> target);

	bool isPressed();
	bool isHold() const;
	// bool isReleased();

	// Getters / Setters
	const std::string getText() const;
	void setText(const std::string& text);

private:
	// Resources
	std::shared_ptr<sf::Font> font;

	sf::RectangleShape shape;
	sf::Text text;

	// Variables
	Button::states state;
	bool wasPressed;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color activeColor;
};

} /* namespace gui */

#endif /* RESOURCES_BUTTON_HPP_ */
