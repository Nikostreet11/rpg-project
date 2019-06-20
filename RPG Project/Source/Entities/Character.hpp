/*
 * Character.h
 *
 *  Created on: Jul 12, 2018
 *      Author: Nikostreet11
 */

#ifndef ENTITIES_CHARACTER_HPP_
#define ENTITIES_CHARACTER_HPP_

#include "pch.hpp"

#include "../Utilities/Randomizer.hpp"

class Character
{
public:
	// Constructor / Destructor
	Character(
			sf::Vector2f position,
			sf::Vector2f size,
			const sf::Texture& spriteset);
	virtual ~Character();

	// Functions
	virtual float attack(Character& target);
	//bool move(Direction direction);

	void update(const float& dt);
	void render(sf::RenderTarget& target);

	// Getters / Setters
	int getAgility() const;
	int getEndurance() const;
	float getHealth() const;
	void setHealth(float health);
	//int getPosX() const;
	//int getPosY() const;
	const std::string& getName() const;

protected:
	//void updateStatistics();

	// Initialization
	void initVariables();

	// Resources
	sf::Sprite sprite;

	// Variables
	sf::Vector2f position;
	sf::Vector2f size;

	std::string name;
	int level;
	float maxHealth;
	float maxMana;
	float maxStamina;
	float health;
	float mana;
	float stamina;
	int strenght;
	int perception;
	int endurance;
	int charm;
	int intelligence;
	int agility;
	int luck;
};

#endif /* CHARACTER_H_ */
