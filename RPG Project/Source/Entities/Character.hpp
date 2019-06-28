/*
 * Character.h
 *
 *  Created on: Jul 12, 2018
 *      Author: Nikostreet11
 */

#ifndef ENTITIES_CHARACTER_HPP_
#define ENTITIES_CHARACTER_HPP_

#include "pch.hpp"

#include "..\Actions\Attack.hpp"
#include "..\Utilities\Randomizer.hpp"

class Character
{
public:
	// Enumerators
	enum State
	{
		Waiting,
		Ready,
		Attacking,
		CastingMagic,
		UsingObject,
		Hurt,
		Hit,
		Dead
	};

	// Constructor / Destructor
	Character(/*
			const sf::Texture& spriteset,
			sf::Vector2f position = {0, 0},
			sf::Vector2f size = {0, 0}*/);
	virtual ~Character();

	// Functions
	//bool move(Direction direction);

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target);

	virtual void resetState();

	std::shared_ptr<Action> getAttack();
	std::shared_ptr<Action> getMagic(const std::string& name);
	std::shared_ptr<Action> getObject(const std::string& name);
	std::shared_ptr<Action> getFlee();

	// Getters / Setters
	void setState(State state);
	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& position);
	const sf::Vector2f getSize() const;
	void setSize(const sf::Vector2f& size);

	std::shared_ptr<Action> getAction(const std::string& actionName);
	const std::string& getName() const;
	void setName(const std::string& name);
	//int getAgility() const;
	//int getEndurance() const;
	float getHealth() const;
	void setHealth(float health);
	float getMana() const;
	void setMana(float mana);
	float getStamina() const;
	void setStamina(float stamina);
	int getStrenght() const;

	//int getPosX() const;
	//int getPosY() const;

protected:
	// Internal

	//void updateStatistics();

	// Initialization
	virtual void initVariables();
	virtual void initStats();
	virtual void initActions();
	void initSprite(
			const sf::Texture& spriteset,
			sf::Vector2f position,
			sf::Vector2f size);

	// Resources
	std::shared_ptr<Action> attack;
	std::map<std::string, std::shared_ptr<Action>> magic;
	std::map<std::string, std::shared_ptr<Action>> objects;
	std::shared_ptr<Action> flee;

	sf::Sprite sprite;

	// Variables
	State state;
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
