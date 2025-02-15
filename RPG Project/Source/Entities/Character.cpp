/*
 * Character.cpp
 *
 *  Created on: Jul 12, 2018
 *      Author: Nikostreet11
 */

#include "Character.hpp"

Character::Character(
		std::map<std::string, std::shared_ptr<sf::Texture>> textures) :
	textures(std::move(textures))
{
	//initVariables();
	initStats();
	initActions();
	initStrategy();
	initAnimations();
	//initSprite(spriteset, position, size);
}

Character::~Character()
{
}

std::shared_ptr<ActionResults> Character::use(
		std::shared_ptr<Action> action,
		std::shared_ptr<Character> target)
{
	for (auto& localAction : actions)
	{
		if (action == localAction)
		{
			return action->use(shared_from_this(), target);
		}
	}

	return nullptr;
}

bool Character::flee()
{
	Randomizer& rand = Randomizer::getInstance();
	return rand.percentageOn(50.f + agility);
}

/*
float Character::attack(Character& target) {
	Randomizer& randomizer = Randomizer::getInstance();
	float damage;
	float accuracy = 50 + agility - target.agility;
	if (randomizer.percentageOn(accuracy)) {
		// strike
		damage = strenght - target.endurance * 0.5;
		float criticalChance = 10 + perception;
		if (randomizer.percentageOn(criticalChance)) {
			// critical damage
			damage *= 1.5;
		}
		Human* human = dynamic_cast<Human*>(&target);
		if (human) {
			// target armor
			if (human->getChestplate() != nullptr) {
				damage -= human->getChestplate()->getArmor() * 0.5;
			}
		}
		if (damage < 0) {
			// block
			damage = 0;
		}
		target.health -= damage;
	}
	else {
		// miss
		damage = 0;
	}
	return damage;
}
*/

/*
void Character::update(const float& dt)
{
}
*/

void Character::update(const float& dt)
{
	statsAnimation->update(dt, 1.f);
	attackAnimation->update(dt, 1.f);
}

void Character::render(sf::RenderTarget& target)
{
	target.draw(sprite);
	statsAnimation->render(target);
}

void Character::resetState()
{
	if (health > maxHealth * 0.3f)
	{
		state = Waiting;
	}
	else if	(health <= 0.f)
	{
		state = Dead;
	}
	else
	{
		state = Hurt;
	}
}

// Getters / Setters
void Character::setState(State state)
{
	this->state = state;
}

const sf::Vector2f& Character::getPosition() const
{
	return sprite.getPosition();
}

void Character::setPosition(const sf::Vector2f& position)
{
	sprite.setPosition(position);
}

const sf::Vector2f Character::getSize() const
{
	return sf::Vector2f(
			sprite.getScale().x * sprite.getTextureRect().width,
			sprite.getScale().y * sprite.getTextureRect().height);
}

void Character::setSize(const sf::Vector2f& size)
{
	sprite.setScale(
			size.x / sprite.getTextureRect().width,
			size.y / sprite.getTextureRect().height);
}

std::shared_ptr<Action> Character::chooseAction()
{
	return strategy->chooseAction(actions);
}

std::shared_ptr<Character> Character::chooseTarget(
		std::vector<std::shared_ptr<Character>> allies,
		std::vector<std::shared_ptr<Character>> enemies)
{

	for (auto ally = allies.begin(); ally < allies.end();)
	{
		if ((*ally)->getHealth() < 0)
		{
			allies.erase(ally);
		}
		else
		{
			ally++;
		}
	}

	for (auto enemy = enemies.begin(); enemy < enemies.end();)
	{
		if ((*enemy)->getHealth() < 0)
		{
			enemies.erase(enemy);
		}
		else
		{
			enemy++;
		}
	}


	return strategy->chooseTarget(allies, enemies);
}

bool Character::hasStrategy() const
{
	if (strategy)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Character::setStrategy(std::shared_ptr<Strategy> strategy)
{
	this->strategy = std::move(strategy);
}

std::vector<std::shared_ptr<Action>>& Character::getActions()
{
	return actions;
}

std::shared_ptr<Action> Character::getAction(const std::string& name)
{
	for (auto& action : actions)
	{
		if (action->getName() == name)
		{
			return action;
		}
	}

	return nullptr;
}

bool Character::isAlive()
{
	if (health > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

const std::string& Character::getName() const
{
	return name;
}

void Character::setName(const std::string& name)
{
	this->name = name;
}

float Character::getMaxHealth() const
{
	return maxHealth;
}

float Character::getMaxMana() const
{
	return maxMana;
}

float Character::getMaxStamina() const
{
	return maxStamina;
}

float Character::getHealth() const
{
	return health;
}

void Character::setHealth(float health)
{
	if (health < 0)
	{
		this->health = 0;
	}
	else if (health > maxHealth)
	{
		this->health = maxHealth;
	}
	else
	{
		this->health = health;
	}

	if (strategy)
	{
		updateStrategy();
	}

	notify();
}

float Character::getMana() const
{
	return mana;
}

void Character::setMana(float mana)
{
	if (mana < 0)
	{
		this->mana = 0;
	}
	else if (mana > maxMana)
	{
		this->mana = maxMana;
	}
	else
	{
		this->mana = mana;
	}

	notify();
}

float Character::getStamina() const
{
	return stamina;
}

void Character::setStamina(float stamina)
{
	if (stamina < 0)
	{
		this->stamina = 0;
	}
	else if (stamina > maxStamina)
	{
		this->stamina = maxStamina;
	}
	else
	{
		this->stamina = stamina;
	}

	notify();
}

int Character::getStrenght() const
{
	return strenght;
}

int Character::getIntelligence() const
{
	return intelligence;
}

int Character::getAgility() const
{
	return agility;
}

const sf::Texture& Character::getTexture()
{
	return *sprite.getTexture();
}

void Character::updateStrategy()
{
	Randomizer& rand = Randomizer::getInstance();

	if (health < maxHealth * 0.5f)
	{
		if (rand.percentageOn(50.f))
		{
			strategy = DefensiveStrategy::getInstance();
		}
		else
		{
			strategy = AggressiveStrategy::getInstance();
		}
	}
	else
	{
		strategy = NaiveStrategy::getInstance();
	}
}

/*
int Character::getAgility() const
{
	return agility;
}

int Character::getEndurance() const
{
	return endurance;
}
*/

// Initialization
void Character::initVariables()
{
	strategy = nullptr;

	spriteOffset = sf::Vector2u(16, 16);
	spriteSize = sf::Vector2u(48, 48);
	spriteSpacing = sf::Vector2u(16, 16);
	spriteIndex = sf::Vector2u(1, 0);
}

void Character::initStats()
{
	name = "Default";
	level = 1;
	maxHealth = 100;
	health = maxHealth;
	maxMana = 30;
	mana = maxMana;
	maxStamina = 30;
	stamina = maxStamina;

	strenght = 1;
	perception = 1;
	endurance = 1;
	charm = 1;
	intelligence = 1;
	agility = 1;
	luck = 1;
}

void Character::initActions()
{
	actions.push_back(std::move(std::make_shared<Attack>()));

	std::vector<Magic::Type> magicList = {
			Magic::Fire,
			Magic::Blizzard,
			Magic::Thunder};

	for (auto& magic : magicList)
	{
		actions.push_back(std::move(std::make_shared<Magic>(magic)));
	}

	std::vector<Object::Type> objectList = {
			Object::Potion,
			Object::Ether,
			Object::Energizer};

	for (auto& object : objectList)
	{
		actions.push_back(std::move(std::make_shared<Object>(object)));
	}
}

void Character::initStrategy()
{
	strategy = nullptr;
}

void Character::initSprite(
		const sf::Texture& textureSheet,
		sf::Vector2f position,
		sf::Vector2f size)
{
	//this->textureSheet = textureSheet;

	sprite.setTexture(textureSheet);
	sprite.setTextureRect(sf::IntRect(
			spriteOffset.x + (spriteSpacing.x + spriteSize.x) * spriteIndex.x,
			spriteOffset.y + (spriteSpacing.y + spriteSize.y) * spriteIndex.y,
			spriteSize.x,
			spriteSize.y));
	sprite.setPosition(position);
	sprite.setScale(
			size.x / sprite.getTextureRect().width,
			size.y / sprite.getTextureRect().height);
}

void Character::playStatsAnimation(int value, Stat stat, bool critical)
{
	statsAnimation->init(value, stat, critical);
	statsAnimation->play();
}

void Character::playAttackAnimation(sf::Vector2f targetPosition,
		sf::Vector2f targetSize)
{
	attackAnimation->init(targetPosition, targetSize);
	attackAnimation->play();
}

void Character::initAnimations()
{
	statsAnimation = std::make_shared<StatsAnimation>(
			1.5f, 2.f,
			sprite, textures["ICONS"].get(),
			sf::Vector2u(2, 2),
			sf::Vector2u(16, 16),
			sf::Vector2u(0, 0));

	attackAnimation = std::make_shared<AttackAnimation>(
			3.f, sprite);
}

/*
bool Character::move(Direction direction) {
	if (posX == NO_POSITION || posY == NO_POSITION) {
		return false;
	}
	else {
		switch (direction) {
		case Direction::up:
			posY--;
			break;
		case Direction::left:
			posX--;
			break;
		case Direction::down:
			posY++;
			break;
		case Direction::right:
			posX++;
			break;
		case Direction::none:
			break;
		}
		return true;
	}
}*/

/*void Character::updateStatistics() {
	maxHealth = level * 10;
	maxMana = level * 10;
	maxStamina = level * 10;

	health = maxHealth;
	mana = maxMana;
	stamina = maxStamina;

	strenght = 1;
	perception = 1;
	endurance = 1;
	charm = 1;
	intelligence = 1;
	agility = 1;
	luck = 1;
}

int Character::getPosX() const {
	return posX;
}

int Character::getPosY() const {
	return posY;
}*/
