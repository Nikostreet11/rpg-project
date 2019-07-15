/*
 * StatsMenu.hpp
 *
 *  Created on: Jul 15, 2019
 *      Author: nicop
 */

#ifndef GUI_STATSMENU_HPP_
#define GUI_STATSMENU_HPP_

#include "pch.hpp"

#include "..\Utilities\Observer.hpp"

#include "..\Entities\Character.hpp"

namespace gui
{

class StatsMenu:
		public Observer,
		public std::enable_shared_from_this<StatsMenu>
{
public:
	// Structures
	struct CharacterInfo
	{
		sf::Sprite characterSprite;

		sf::Text healthText;
		sf::Sprite healthSprite;

		sf::Text manaText;
		sf::Sprite manaSprite;

		sf::Text staminaText;
		sf::Sprite staminaSprite;
	};

	explicit StatsMenu(
			sf::Vector2f position,
			std::map<std::string, std::shared_ptr<sf::Texture>> textures,
			std::shared_ptr<sf::Font> font);
	virtual ~StatsMenu();

	virtual void update();
	virtual void render(sf::RenderTarget& target);

	virtual void addSubject(std::shared_ptr<Character> subject);
	//virtual void removeSubject(std::shared_ptr<Character> subject);

private:
	// Initialization
	void initBackground();

	// Resources
	std::vector<std::shared_ptr<Character>> subjects;

	std::map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::shared_ptr<sf::Font> font;

	sf::RectangleShape background;

	std::vector<CharacterInfo> subjectsInfo;

	// Variables
	sf::Vector2f position;
};

} /* namespace gui */

#endif /* GUI_STATSMENU_HPP_ */
