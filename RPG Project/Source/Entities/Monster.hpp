/*
 * Monster.hpp
 *
 *  Created on: Jun 20, 2019
 *      Author: nicop
 */

#ifndef ENTITIES_MONSTER_HPP_
#define ENTITIES_MONSTER_HPP_

#include "Character.hpp"

class Monster:
		public Character
{
public:
	// Enumerators
	enum Type
	{
		Goblin,
		Wolf,
		Piranha,
		Skeleton,
		BlackWidow,
		GigasWorm,
		WargWolf,
		Werewolf,
		Zombie
	};

	// Constructor / Destructor
	explicit Monster(
			Type type,
			std::map<std::string, std::shared_ptr<sf::Texture>> textures,
			sf::Vector2f position = {0, 0},
			sf::Vector2f size = {0, 0});
	virtual ~Monster();

	// Functions
	virtual void update(const float& dt);
	void updateSpriteSequenceAnimations(const float& dt);

	// Getters / Setters
	virtual bool isWeakToFire() const;
	virtual bool isWeakToIce() const;
	virtual bool isWeakToLightning() const;

private:
	// Initialization
	virtual void initVariables() override;
	virtual void initStats() override;
	virtual void initSpriteSequenceAnimations();

	// Variables
	Type type;

	bool weakToFire;
	bool weakToIce;
	bool weakToLightning;
};

#endif /* ENTITIES_MONSTER_HPP_ */
