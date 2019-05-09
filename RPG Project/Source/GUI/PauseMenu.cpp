/*
 * PauseMenu.cpp
 *
 *  Created on: May 9, 2019
 *      Author: nicop
 */

#include "PauseMenu.hpp"

PauseMenu::PauseMenu(std::shared_ptr<sf::RenderWindow> window)
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
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::update(const float& dt)
{
}

void PauseMenu::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (target)
	{
		target->draw(background);
		target->draw(container);

		for (auto &i : buttons)
		{
			i.second->render(target);
		}
	}
}
