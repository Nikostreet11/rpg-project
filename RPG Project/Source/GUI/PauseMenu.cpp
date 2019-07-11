/*
 * PauseMenu.cpp
 *
 *  Created on: May 9, 2019
 *      Author: nicop
 */

#include "PauseMenu.hpp"

namespace gui
{

PauseMenu::PauseMenu(
		std::shared_ptr<sf::RenderWindow> window,
		std::shared_ptr<sf::Font> font) :
font(std::move(font))
{
	// Initialize background
	background.setSize(
		sf::Vector2f(
			static_cast<float>(window->getSize().x),
			static_cast<float>(window->getSize().y)
		)
	);
	background.setFillColor(sf::Color(20, 20, 20, 100));

	// Initialize container
	container.setSize(
		sf::Vector2f(
			static_cast<float>(window->getSize().x) / 4.f,
			static_cast<float>(window->getSize().y) - 60.f
		)
	);
	container.setFillColor(sf::Color(20, 20, 20, 100));
	container.setPosition(
		sf::Vector2f(
			static_cast<float>(window->getSize().x) / 2.f -
					container.getSize().x / 2.f,
			30.f
		)
	);

	// Initialize text
	menuText.setFont(*this->font);
	menuText.setFillColor(sf::Color(255, 255, 255, 200));
	menuText.setCharacterSize(60);
	menuText.setString("PAUSED");
	menuText.setPosition(
			container.getPosition().x + container.getSize().x / 2.f -
					menuText.getGlobalBounds().width / 2.f,
			container.getPosition().y + 40.f
	);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::addButton(
		const std::string key,
		float y,
		const std::string text)
{
	sf::Vector2f size(250.f, 100.f);

	float x = container.getPosition().x + container.getSize().x / 2.f -
			size.x / 2.f;

	buttons[key].reset(new gui::Button(
			// Position
			sf::Vector2f(x, y),
			// Size
			size,
			// Text options
			font, text, 50,
			sf::Color(150, 150, 150, 250),
			sf::Color(250, 250, 250, 250),
			sf::Color(220, 220, 220, 250),
			// Button colors
			sf::Color(150, 150, 150, 0),
			sf::Color(250, 250, 250, 0),
			sf::Color(220, 220, 220, 0))
	);
}

bool PauseMenu::isButtonPressed(const std::string& key)
{
	return buttons[key]->isPressed();
}

void PauseMenu::update(const sf::Vector2i& mousePosWindow)
{
	for (auto &i : buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);

	for (auto &i : buttons)
	{
		i.second->render(target);
	}

	target.draw(menuText);
}

std::map<std::string, std::unique_ptr<gui::Button>>& PauseMenu::getButtons()
{
	return buttons;
}

} /* namespace gui */

