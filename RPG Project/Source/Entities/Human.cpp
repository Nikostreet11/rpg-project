/*
 * Human.cpp
 *
 *  Created on: Jul 18, 2018
 *      Author: Nikostreet11
 */

#include "Human.hpp"

Human::Human(
		Type type,
		const sf::Texture& spriteset,
		sf::Vector2f position,
		sf::Vector2f size) :
		Character()
{
	this->type = type;

	initVariables();
	initStats();
	initSprite(spriteset, position, size);
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

		animationComponent->play("HIT", dt);
		break;

	case Dead:

		animationComponent->play("DEAD", dt);
		break;
	}
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
	animationComponent->addAnimation("WAIT", 0.3f, indexVector);

	indexVector = {{1, 0}};
	animationComponent->addAnimation("READY", 0.3f, indexVector);

	indexVector = {
			{2, 0}, {4, 0}, {2, 0},
			{4, 0}, {4, 0}, {4, 0}, {3, 0}, {3, 0},
			{2, 0}, {4, 0}, {2, 0}};
	animationComponent->addAnimation("ATTACK", 0.15f, indexVector);

	indexVector = {
			{5, 0}, {6, 0}, {5, 0}, {6, 0}, {5, 0}, {6, 0},
			{5, 0}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}};
	animationComponent->addAnimation("CAST_MAGIC", 0.3f, indexVector);

	indexVector = {{0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}};
	animationComponent->addAnimation("USE_OBJECT", 0.3f, indexVector);

	indexVector = {{1, 1}};
	animationComponent->addAnimation("HURT", 0.3f, indexVector);

	indexVector = {{2, 1}};
	animationComponent->addAnimation("HIT", 0.3f, indexVector);

	indexVector = {{3, 1}};
	animationComponent->addAnimation("DEAD", 0.3f, indexVector);
}
