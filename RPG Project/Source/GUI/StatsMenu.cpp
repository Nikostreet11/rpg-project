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
		healthString << subject.getHealth() << " / " << subject.getMaxHealth();
		subjectInfo.healthText.setString(healthString.str());

		std::stringstream manaString;
		manaString << subject.getMana() << " / " << subject.getMaxMana();
		subjectInfo.manaText.setString(manaString.str());

		std::stringstream staminaString;
		staminaString << subject.getStamina() << " / " << subject.getMaxStamina();
		subjectInfo.staminaText.setString(staminaString.str());
	}
}

void StatsMenu::render(sf::RenderTarget& target)
{
	target.draw(background);

	for (auto& subjectInfo : subjectsInfo)
	{
		// target.draw(subjectInfo.healthSprite);
		target.draw(subjectInfo.healthText);
		// target.draw(subjectInfo.manaSprite);
		target.draw(subjectInfo.manaText);
		// target.draw(subjectInfo.staminaSprite);
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

	subjectInfo.characterSprite.setTexture(subject->getTexture());
	subjectInfo.characterSprite.setTextureRect(sf::IntRect(16, 16, 48, 48));
	// subjectInfo.healthSprite.setScale(x, x);
	subjectInfo.characterSprite.setPosition(position);
	subjectInfo.characterSprite.move(600.f, 10.f + 40.f * index);

	// TODO: add STAT_ICONS texture to textures
	// subjectInfo.healthSprite.setTexture(textures["STATS_ICONS"]);
	// subjectInfo.healthSprite.setTextureRect(sf::IntRect(x, x, x, x));
	// subjectInfo.healthSprite.setScale(x, x);
	subjectInfo.healthSprite.setPosition(position);
	subjectInfo.healthSprite.move(50.f, 10.f + 40.f * index);

	// TODO: add STAT_ICONS texture to textures
	// subjectInfo.manaSprite.setTexture(textures["STATS_ICONS"]);
	// subjectInfo.manaSprite.setTextureRect(sf::IntRect(x, x, x, x));
	// subjectInfo.manaSprite.setScale(x, x);
	subjectInfo.manaSprite.setPosition(position);
	subjectInfo.manaSprite.move(200.f, 10.f + 40.f * index);

	// TODO: add STAT_ICONS texture to textures
	// subjectInfo.staminaSprite.setTexture(textures["STATS_ICONS"]);
	// subjectInfo.staminaSprite.setTextureRect(sf::IntRect(x, x, x, x));
	// subjectInfo.staminaSprite.setScale(x, x);
	subjectInfo.staminaSprite.setPosition(position);
	subjectInfo.staminaSprite.move(350.f, 10.f + 40.f * index);

	subjectInfo.healthText.setPosition(position);
	subjectInfo.healthText.move(100.f, 10.f + 40.f * index);
	subjectInfo.healthText.setFont(*font);
	subjectInfo.healthText.setCharacterSize(20);
	subjectInfo.healthText.setFillColor(sf::Color::White);

	std::stringstream healthString;
	healthString << subject->getHealth() << " / " << subject->getMaxHealth();
	subjectInfo.healthText.setString(healthString.str());

	subjectInfo.manaText.setPosition(position);
	subjectInfo.manaText.move(250.f, 10.f + 40.f * index);
	subjectInfo.manaText.setFont(*font);
	subjectInfo.manaText.setCharacterSize(20);
	subjectInfo.manaText.setFillColor(sf::Color::White);

	std::stringstream manaString;
	manaString << subject->getMana() << " / " << subject->getMaxMana();
	subjectInfo.manaText.setString(manaString.str());

	subjectInfo.staminaText.setPosition(position);
	subjectInfo.staminaText.move(400.f, 10.f + 40.f * index);
	subjectInfo.staminaText.setFont(*font);
	subjectInfo.staminaText.setCharacterSize(20);
	subjectInfo.staminaText.setFillColor(sf::Color::White);

	std::stringstream staminaString;
	staminaString << subject->getStamina() << " / " << subject->getMaxStamina();
	subjectInfo.staminaText.setString(staminaString.str());

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
	background.setSize(sf::Vector2f(600.f, 300.f));
	background.setFillColor(sf::Color(0, 0, 0, 150));
}

} /* namespace gui */
