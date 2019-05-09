/*
 * Player.hpp
 *
 *  Created on: Apr 24, 2019
 *      Author: nicop
 */

#ifndef ENTITIES_PLAYER_HPP_
#define ENTITIES_PLAYER_HPP_

#include "Entity.hpp"

class Player:
		public Entity
{
public:
	// Constructors / Destructors
	Player(sf::Vector2f position, std::shared_ptr<sf::Texture> textureSheet);
	virtual ~Player();

	// Functions
	virtual void update(const float& dt) override;
	void updateAnimations(const float& dt);

private:
	// Initialization functions
	void initVariables();
	void initAnimations();

	// Variables
};

#endif /* ENTITIES_PLAYER_HPP_ */
