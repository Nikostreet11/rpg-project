/*
 * Monster.cpp
 *
 *  Created on: Jun 20, 2019
 *      Author: nicop
 */

#include "Monster.hpp"

Monster::Monster(
		Type type,
		std::map<std::string, std::shared_ptr<sf::Texture>> textures,
		sf::Vector2f position,
		sf::Vector2f size) :
		Character(textures)
{
	this->type = type;

	initVariables();
	initStats();
	initSprite(*textures["MONSTERS"], position, size);
	initSpriteSequenceAnimations();
}

Monster::~Monster()
{
}

// Functions
void Monster::update(const float& dt)
{
	Character::update(dt);
	updateSpriteSequenceAnimations(dt);
}

void Monster::updateSpriteSequenceAnimations(const float& dt)
{
	switch (state)
	{

	case Waiting:
	case Ready:
	case Attacking:
	case CastingMagic:
	case UsingObject:
	case Hurt:
	case Victorious:

		animationComponent->play("WAIT", dt);
		break;

	case Hit:

		animationComponent->play("HIT", dt);

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

// Getters / Setters
bool Monster::isWeakToFire() const
{
	return weakToFire;
}

bool Monster::isWeakToIce() const
{
	return weakToIce;
}

bool Monster::isWeakToLightning() const
{
	return weakToLightning;
}

// Initialization
void Monster::initVariables()
{
	spriteOffset = {0, 0};
	spriteSize = {64, 64};
	spriteSpacing = {2, 2};

	weakToFire = false;
	weakToIce = false;
	weakToLightning = false;

	switch (type)
	{
	case Goblin:
		spriteIndex = {0, 0};
		break;

	case Wolf:
		spriteIndex = {8, 0};
		break;

	case Piranha:
		spriteIndex = {9, 4};
		break;

	case Skeleton:
		spriteIndex = {7, 2};
		break;

	case BlackWidow:
		spriteIndex = {5, 4};
		break;

	case GigasWorm:
		spriteIndex = {9, 2};
		break;

	case WargWolf:
		spriteIndex = {4, 1};
		break;

	case Werewolf:
		spriteIndex = {9, 1};
		break;

	case Zombie:
		spriteIndex = {0, 1};
		break;

	default:
		spriteIndex = {0, 0};
		break;
	}
}

void Monster::initStats()
{
	switch (type)
	{
	case Goblin:
		name = "Goblin";
		weakToLightning = true;
		agility = 2;
		break;

	case Wolf:
		name = "Wolf";
		weakToFire = true;
		agility = 4;
		break;

	case Piranha:
		name = "Piranha";
		weakToLightning = true;
		break;

	case Skeleton:
		name = "Skeleton";
		weakToIce = true;
		break;

	case BlackWidow:
		name = "Black widow";
		weakToIce = true;
		agility = 3;
		break;

	case GigasWorm:
		name = "Gigas worm";
		weakToFire = true;
		break;

	case WargWolf:
		name = "Warg wolf";
		weakToIce = true;
		agility = 4;
		break;

	case Werewolf:
		name = "Werewolf";
		weakToLightning = true;
		agility = 4;
		break;

	case Zombie:
		name = "Zombie";
		weakToFire = true;
		break;

	default:
		break;
	}
}

void Monster::initSpriteSequenceAnimations()
{
	animationComponent.reset(new AnimationComponent(sprite));

	std::vector<sf::Vector2u> indexVector;
	std::shared_ptr<SpriteSequenceAnimation> animation;

	indexVector = {spriteIndex};
	animation =	std::make_shared<SpriteSequenceAnimation>(
			true, 0.f, 0.3f,
			sprite, nullptr,
			indexVector,
			spriteOffset,
			spriteSize,
			spriteSpacing);
	animationComponent->addAnimation("WAIT", std::move(animation));

	indexVector = {
			{8, 8}, spriteIndex, {8, 8}, spriteIndex,
			{8, 8}, spriteIndex, {8, 8}, spriteIndex,
			{8, 8}, spriteIndex, {8, 8}, spriteIndex};
	animation =	std::make_shared<SpriteSequenceAnimation>(
			false, 1.5f, 1.f,
			sprite, nullptr,
			indexVector,
			spriteOffset,
			spriteSize,
			spriteSpacing);
	animationComponent->addAnimation("HIT", std::move(animation));

	indexVector = {{8, 8}};
	animation =	std::make_shared<SpriteSequenceAnimation>(
			true, 0.f, 0.3f,
			sprite, nullptr,
			indexVector,
			spriteOffset,
			spriteSize,
			spriteSpacing);
	animationComponent->addAnimation("DEAD", std::move(animation));
}
