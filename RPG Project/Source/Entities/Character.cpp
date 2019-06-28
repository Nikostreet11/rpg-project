/*
 * Character.cpp
 *
 *  Created on: Jul 12, 2018
 *      Author: Nikostreet11
 */

#include "Character.hpp"

Character::Character(/*
		const sf::Texture& spriteset,
		sf::Vector2f position,
		sf::Vector2f size*/)
{
	//initVariables();
	initStats();
	initActions();
	//initSprite(spriteset, position, size);
}

Character::~Character()
{
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

void Character::render(sf::RenderTarget& target)
{
	target.draw(sprite);
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

std::shared_ptr<Action> Character::getAction(const std::string& actionName)
{
	// TODO: rework getting the right action based on the request;
	return attack;
}

const std::string& Character::getName() const
{
	return name;
}

void Character::setName(const std::string& name)
{
	this->name = name;
}

float Character::getHealth() const
{
	return health;
}

void Character::setHealth(float health)
{
	this->health = health;
}

float Character::getMana() const
{
	return mana;
}

void Character::setMana(float mana)
{
	this->mana = mana;
}

float Character::getStamina() const
{
	return stamina;
}

void Character::setStamina(float stamina)
{
	this->stamina = stamina;
}

int Character::getStrenght() const
{
	return strenght;
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
	attack = std::make_shared<Attack>();
}

void Character::initSprite(
		const sf::Texture& spriteset,
		sf::Vector2f position,
		sf::Vector2f size)
{
	sprite.setTexture(spriteset);
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
