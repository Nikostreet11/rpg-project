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
	Character(/*
			const sf::Texture& spriteset,
			sf::Vector2f position = {0, 0},
			sf::Vector2f size = {0, 0}*/);
	virtual ~Character();

	// Functions
	//virtual float attack(Character& target);
	//bool move(Direction direction);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);

	// Getters / Setters
	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& position);
	const sf::Vector2f getSize() const;
	void setSize(const sf::Vector2f& size);

	//int getAgility() const;
	//int getEndurance() const;
	//float getHealth() const;
	//void setHealth(float health);
	//int getPosX() const;
	//int getPosY() const;
	//const std::string& getName() const;

protected:
	// Internal

	//void updateStatistics();

	// Initialization
	virtual void initVariables();
	void initStats();
	void initSprite(
			const sf::Texture& spriteset,
			sf::Vector2f position,
			sf::Vector2f size);

	// Resources
	sf::Sprite sprite;

	// Variables
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

	sf::Vector2u spriteOffset;
	sf::Vector2u spriteSize;
	sf::Vector2u spriteSpacing;
	sf::Vector2u spriteIndex;
};

#endif /* ENTITIES_CHARACTER_HPP_ */
