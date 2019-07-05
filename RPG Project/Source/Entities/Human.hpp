/*
 * Human.h
 *
 *  Created on: Jul 18, 2018
 *      Author: Nikostreet11
 */

#ifndef ENTITIES_HUMAN_HPP_
#define ENTITIES_HUMAN_HPP_

#include "Character.hpp"
//#include "..\Exclude\Chestplate.h"
//#include "..\Exclude\Weapon.h"

class Human:
		public Character
{
public:
	// Enumerators
	enum Type
	{
		BlackMage,
		BlackWizard,
		Knight,
		Master,
		Monk,
		Ninja,
		RedMage,
		RedWizard,
		Thief,
		Warrior,
		WhiteMage,
		WhiteWizard
	};

	// Constructor / Destructor
	explicit Human(
			Type type,
			std::map<std::string, std::shared_ptr<sf::Texture>> textures,
			sf::Vector2f position = {0, 0},
			sf::Vector2f size = {0, 0});
	virtual ~Human();

	// Functions
	virtual void update(const float& dt);
	virtual void updateAnimations(const float& dt);

	// Getters / Setters
	virtual bool isWeakToFire() const;
	virtual bool isWeakToIce() const;
	virtual bool isWeakToLightning() const;

	//virtual float attack(Character& target);
	/*
	const Chestplate* getChestplate() const;
	void setChestplate(Chestplate* chestplate);
	const Weapon* getWeapon() const;
	void setWeapon(Weapon* weapon);
	*/

protected:
	// Internal
	const sf::Texture& getTexture(
			std::map<std::string, std::shared_ptr<sf::Texture>> textures);

	// Initialization
	virtual void initVariables() override;
	virtual void initStats() override;
	virtual void initAnimations();

	// Variables
	Type type;
	/*
	Weapon* weapon;
	Helmet head;
	Gauntlets arms;
	Chestplate* chestplate;
	Greaves legs;
	Boots feet;
	*/
};

#endif /* ENTITIES_HUMAN_HPP_ */
