/*
 * StatsMenu.cpp
 *
 *  Created on: Jul 15, 2019
 *      Author: nicop
 */

#include "StatsMenu.hpp"

namespace gui {

StatsMenu::StatsMenu(
		sf::Vector2f position,
		std::map<std::string, std::shared_ptr<sf::Texture>> textures,
		std::shared_ptr<sf::Font> font)
{
	this->position = position;

	this->textures = textures;
	this->font = font;

	initBackground();
}

StatsMenu::~StatsMenu()
{
}

void StatsMenu::update()
{
	for (size_t index = 0; index < subjects.size(); index++)
	{
		Character& subject = *subjects[index];
		CharacterInfo& subjectInfo = subjectsInfo[index];

		std::stringstream healthString;
		healthString <<
				std::round(subject.getHealth()) << "/" <<
				std::round(subject.getMaxHealth());
		subjectInfo.healthText.setString(healthString.str());

		std::stringstream manaString;
		manaString <<
				std::round(subject.getMana()) << "/" <<
				std::round(subject.getMaxMana());
		subjectInfo.manaText.setString(manaString.str());

		std::stringstream staminaString;
		staminaString <<
				std::round(subject.getStamina()) << "/" <<
				std::round(subject.getMaxStamina());
		subjectInfo.staminaText.setString(staminaString.str());
	}
}

void StatsMenu::render(sf::RenderTarget& target)
{
	target.draw(background);

	for (auto& subjectInfo : subjectsInfo)
	{
		target.draw(subjectInfo.healthSprite);
		target.draw(subjectInfo.healthText);
		target.draw(subjectInfo.manaSprite);
		target.draw(subjectInfo.manaText);
		target.draw(subjectInfo.staminaSprite);
		target.draw(subjectInfo.staminaText);
		target.draw(subjectInfo.characterSprite);
	}
}

void StatsMenu::addSubject(std::shared_ptr<Character> subject)
{
	subjects.push_back(subject);

	subjectsInfo.resize(subjectsInfo.size() + 1);

	CharacterInfo& subjectInfo = subjectsInfo[subjectsInfo.size() - 1];
	unsigned index = subjectsInfo.size() - 1;

	subjectInfo.healthSprite.setTexture(*textures["STATS"]);
	subjectInfo.healthSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
	subjectInfo.healthSprite.setPosition(position);
	subjectInfo.healthSprite.move(10.f, 10.f + 50.f * index);

	subjectInfo.healthText.setPosition(position);
	subjectInfo.healthText.move(60.f, 10.f + 50.f * index);
	subjectInfo.healthText.setFont(*font);
	subjectInfo.healthText.setCharacterSize(40);
	subjectInfo.healthText.setFillColor(sf::Color::White);

	subjectInfo.manaSprite.setTexture(*textures["STATS"]);
	subjectInfo.manaSprite.setTextureRect(sf::IntRect(50, 0, 50, 50));
	subjectInfo.manaSprite.setPosition(position);
	subjectInfo.manaSprite.move(210.f, 10.f + 50.f * index);

	subjectInfo.manaText.setPosition(position);
	subjectInfo.manaText.move(260.f, 10.f + 50.f * index);
	subjectInfo.manaText.setFont(*font);
	subjectInfo.manaText.setCharacterSize(40);
	subjectInfo.manaText.setFillColor(sf::Color::White);

	subjectInfo.staminaSprite.setTexture(*textures["STATS"]);
	subjectInfo.staminaSprite.setTextureRect(sf::IntRect(100, 0, 50, 50));
	subjectInfo.staminaSprite.setPosition(position);
	subjectInfo.staminaSprite.move(410.f, 10.f + 50.f * index);

	subjectInfo.staminaText.setPosition(position);
	subjectInfo.staminaText.move(460.f, 10.f + 50.f * index);
	subjectInfo.staminaText.setFont(*font);
	subjectInfo.staminaText.setCharacterSize(40);
	subjectInfo.staminaText.setFillColor(sf::Color::White);

	subjectInfo.characterSprite.setTexture(subject->getTexture());
	subjectInfo.characterSprite.setTextureRect(sf::IntRect(16, 16, 48, 48));
	subjectInfo.characterSprite.setPosition(position);
	subjectInfo.characterSprite.move(620.f, 10.f + 50.f * index);

	subject->attach(shared_from_this());
}

/*
void StatsMenu::removeSubject(std::shared_ptr<Character> subject)
{
}
*/

void StatsMenu::initBackground()
{
	background.setPosition(position);
	background.setSize(sf::Vector2f(680.f, 220.f));
	background.setFillColor(sf::Color(0, 0, 0, 150));
}

} /* namespace gui */
