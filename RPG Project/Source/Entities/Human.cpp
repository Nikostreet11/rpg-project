/*
 * Human.cpp
 *
 *  Created on: Jul 18, 2018
 *      Author: Nikostreet11
 */

#include "Human.hpp"

Human::Human(
		Type type,
		std::map<std::string, std::shared_ptr<sf::Texture>> textures,
		sf::Vector2f position,
		sf::Vector2f size) :
		Character(textures)
{
	this->type = type;

	initVariables();
	initStats();
	initSprite(getTexture(textures), position, size);
	initAnimations();
	/*
	weapon = nullptr;
	chestplate = nullptr;
	*/
}

Human::~Human()
{
}

// Functions
void Human::update(const float& dt)
{
	Character::update(dt);
	updateAnimations(dt);
}

void Human::updateAnimations(const float& dt)
{
	switch (state)
	{
	case Waiting:

		animationComponent->play("WAIT", dt);
		break;

	case Ready:

		animationComponent->play("READY", dt);
		break;

	case Attacking:

		animationComponent->play("ATTACK", dt, true);

		if (animationComponent->isDone("ATTACK"))
		{
			resetState();
		}
		break;

	case CastingMagic:

		animationComponent->play("CAST_MAGIC", dt, true);

		if (animationComponent->isDone("CAST_MAGIC"))
		{
			resetState();
		}
		break;

	case UsingObject:

		animationComponent->play("USE_OBJECT", dt, true);

		if (animationComponent->isDone("USE_OBJECT"))
		{
			resetState();
		}
		break;

	case Hurt:

		animationComponent->play("HURT", dt);
		break;

	case Hit:

		animationComponent->play("HIT", dt, true);

		if (animationComponent->isDone("HIT"))
		{
			resetState();
		}
		break;

	case Dead:

		animationComponent->play("DEAD", dt);
		break;
	}
}

bool Human::isWeakToFire() const
{
	return false;
}

bool Human::isWeakToIce() const
{
	return false;
}

bool Human::isWeakToLightning() const
{
	return false;
}

/*
float Human::attack(Character& target)
{
	Randomizer& randomizer = Randomizer::getInstance();
	float damage;
	float accuracy = 50 + agility - target.getAgility();
	if (randomizer.percentageOn(accuracy)) {
		// strike
		damage = strenght - target.getEndurance() * 0.5;
		if (weapon != nullptr) {
			// weapon damage
			damage += weapon->getImpact();
		}
		float criticalChance = 10 + perception;
		if (randomizer.percentageOn(criticalChance)) {
			// critical damage
			damage *= 1.5;
		}
		Human* human = dynamic_cast<Human*>(&target);
		if (human) {
			// target armor
			if (human->chestplate != nullptr) {
				damage -= human->chestplate->getArmor() * 0.5;
			}
		}
		if (damage < 0) {
			// block
			damage = 0;
		}
		target.setHealth(target.getHealth() - damage);
	}
	else {
		// miss
		damage = 0;
	}
	return damage;
}
*/

/*
const Chestplate* Human::getChestplate() const {
	return chestplate;
}

void Human::setChestplate(Chestplate* chestplate) {
	this->chestplate = chestplate;
}

const Weapon* Human::getWeapon() const {
	return weapon;
}

void Human::setWeapon(Weapon* weapon) {
	this->weapon = weapon;
}
*/

// Internal
const sf::Texture& Human::getTexture(
		std::map<std::string, std::shared_ptr<sf::Texture>> textures)
{
	switch (type)
	{
	case BlackMage:
		return *textures["BLACK_MAGE"];
		break;

	case BlackWizard:
		break;

	case Knight:
		break;

	case Master:
		break;

	case Monk:
		break;

	case Ninja:
		break;

	case RedMage:
		break;

	case RedWizard:
		break;

	case Thief:
		return *textures["THIEF"];
		break;

	case Warrior:
		return *textures["WARRIOR"];
		break;

	case WhiteMage:
		return *textures["WHITE_MAGE"];
		break;

	case WhiteWizard:
		break;
	}

	return *textures["WARRIOR"];
}

// Initialization
void Human::initVariables()
{
	state = Waiting;

	spriteOffset = {16, 16};
	spriteSize = {48, 48};
	spriteSpacing = {16, 16};
	spriteIndex = {1, 0};
}

void Human::initStats()
{
	switch (type)
	{
	case BlackMage:
		name = "Black mage";
		break;

	case BlackWizard:
		name = "Black wizard";
		break;

	case Knight:
		name = "Knight";
		break;

	case Master:
		name = "Master";
		break;

	case Monk:
		name = "Monk";
		break;

	case Ninja:
		name = "Ninja";
		break;

	case RedMage:
		name = "Red mage";
		break;

	case RedWizard:
		name = "Red wizard";
		break;

	case Thief:
		name = "Thief";
		break;

	case Warrior:
		name = "Warrior";
		break;

	case WhiteMage:
		name = "White mage";
		break;

	case WhiteWizard:
		name = "White wizard";
		break;

	default:
		break;
	}
}

void Human::initAnimations()
{
	animationComponent.reset(new AnimationComponent(sprite,
			{16, 16}, {48, 48}, {16, 16}));

	std::vector<sf::Vector2u> indexVector;

	indexVector = {{0, 0}};
	animationComponent->addAnimation(
			"WAIT",
			std::move(std::make_shared<Animation>(
					sprite, *sprite.getTexture(),
					0.3f, indexVector,
					sf::Vector2u(16, 16),
					sf::Vector2u(48, 48),
					sf::Vector2u(16, 16))));
	//animationComponent->addAnimation("WAIT", 0.3f, indexVector);

	indexVector = {{1, 0}};
	animationComponent->addAnimation(
			"READY",
			std::move(std::make_shared<Animation>(
					sprite, *sprite.getTexture(),
					0.3f, indexVector,
					sf::Vector2u(16, 16),
					sf::Vector2u(48, 48),
					sf::Vector2u(16, 16))));

	indexVector = {
			{2, 0}, {4, 0}, {2, 0}, {2, 0},
			{4, 0}, {4, 0}, {4, 0}, {3, 0}, {3, 0},
			{2, 0}, {4, 0}, {2, 0}};
	animationComponent->addAnimation(
			"ATTACK",
			std::move(std::make_shared<Animation>(
					sprite, *sprite.getTexture(),
					0.15f, indexVector,
					sf::Vector2u(16, 16),
					sf::Vector2u(48, 48),
					sf::Vector2u(16, 16))));

	indexVector = {
			{5, 0}, {6, 0}, {5, 0}, {6, 0}, {5, 0}, {6, 0},
			{5, 0}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}};
	animationComponent->addAnimation(
			"CAST_MAGIC",
			std::move(std::make_shared<Animation>(
					sprite, *sprite.getTexture(),
					0.3f, indexVector,
					sf::Vector2u(16, 16),
					sf::Vector2u(48, 48),
					sf::Vector2u(16, 16))));

	indexVector = {{0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}};
	animationComponent->addAnimation(
			"USE_OBJECT",
			std::move(std::make_shared<Animation>(
					sprite, *sprite.getTexture(),
					0.3f, indexVector,
					sf::Vector2u(16, 16),
					sf::Vector2u(48, 48),
					sf::Vector2u(16, 16))));

	indexVector = {{1, 1}};
	animationComponent->addAnimation(
			"HURT",
			std::move(std::make_shared<Animation>(
					sprite, *sprite.getTexture(),
					0.3f, indexVector,
					sf::Vector2u(16, 16),
					sf::Vector2u(48, 48),
					sf::Vector2u(16, 16))));

	indexVector = {{1, 0}, {1, 0}, {2, 1}, {2, 1}, {2, 1}, {2, 1}};
	animationComponent->addAnimation(
			"HIT",
			std::move(std::make_shared<Animation>(
					sprite, *sprite.getTexture(),
					0.3f, indexVector,
					sf::Vector2u(16, 16),
					sf::Vector2u(48, 48),
					sf::Vector2u(16, 16))));

	indexVector = {{3, 1}};
	animationComponent->addAnimation(
			"DEAD",
			std::move(std::make_shared<Animation>(
					sprite, *sprite.getTexture(),
					0.3f, indexVector,
					sf::Vector2u(16, 16),
					sf::Vector2u(48, 48),
					sf::Vector2u(16, 16))));
}
