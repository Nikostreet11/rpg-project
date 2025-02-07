/*
 * Character.h
 *
 *  Created on: Jul 12, 2018
 *      Author: Nikostreet11
 */

#ifndef ENTITIES_CHARACTER_HPP_
#define ENTITIES_CHARACTER_HPP_

#include "pch.hpp"

#include "../Utilities/Stat.hpp"
#include "..\Utilities\Subject.hpp"

#include "..\Actions\Attack.hpp"
#include "..\Actions\Magic.hpp"
#include "..\Actions\Object.hpp"
#include "..\Utilities\Randomizer.hpp"
#include "..\Containers\ActionResults.hpp"
#include "..\Strategies\NaiveStrategy.hpp"
#include "..\Strategies\AggressiveStrategy.hpp"
#include "..\Strategies\DefensiveStrategy.hpp"

#include "..\Components\AnimationComponent.hpp"
#include "..\Animations\StatsAnimation.hpp"
#include "..\Animations\AttackAnimation.hpp"


class Character:
		public Subject,
		public std::enable_shared_from_this<Character>
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
		Dead,
		Victorious
	};

	// Constructor / Destructor
	explicit Character(
			std::map<std::string,
			std::shared_ptr<sf::Texture>> textures);
	virtual ~Character() = 0;

	// Functions
	virtual std::shared_ptr<ActionResults> use(
			std::shared_ptr<Action> action,
			std::shared_ptr<Character> target);
	virtual bool flee();

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);

	virtual void resetState();

	void playStatsAnimation(
			int value,
			Stat stat,
			bool critical);

	void playAttackAnimation(
			sf::Vector2f targetPosition,
			sf::Vector2f targetSize);

	// Getters / Setters
	void setState(State state);
	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& position);
	const sf::Vector2f getSize() const;
	void setSize(const sf::Vector2f& size);

	std::shared_ptr<Action> chooseAction();
	std::shared_ptr<Character> chooseTarget(
			std::vector<std::shared_ptr<Character>> allies,
			std::vector<std::shared_ptr<Character>> enemies);
	bool hasStrategy() const;
	void setStrategy(std::shared_ptr<Strategy> strategy);

	std::vector<std::shared_ptr<Action>>& getActions();
	std::shared_ptr<Action> getAction(const std::string& actionName);
	bool isAlive();

	const std::string& getName() const;
	void setName(const std::string& name);
	float getMaxHealth() const;
	float getMaxMana() const;
	float getMaxStamina() const;
	float getHealth() const;
	void setHealth(float health);
	float getMana() const;
	void setMana(float mana);
	float getStamina() const;
	void setStamina(float stamina);
	int getStrenght() const;
	int getIntelligence() const;
	int getAgility() const;

	virtual bool isWeakToFire() const = 0;
	virtual bool isWeakToIce() const = 0;
	virtual bool isWeakToLightning() const = 0;

	const sf::Texture& getTexture();

protected:
	// Internal
	virtual void updateStrategy();

	//void updateStatistics();

	// Initialization
	virtual void initVariables();
	virtual void initStats();
	virtual void initActions();
	virtual void initStrategy();
	void initSprite(
			const sf::Texture& textureSheet,
			sf::Vector2f position,
			sf::Vector2f size);
	virtual void initAnimations();

	// Resources
	sf::Sprite sprite;
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;

	std::vector<std::shared_ptr<Action>> actions;

	std::shared_ptr<Strategy> strategy;

	std::shared_ptr<AnimationComponent> animationComponent;
	std::shared_ptr<StatsAnimation> statsAnimation;
	std::shared_ptr<AttackAnimation> attackAnimation;

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
