/*
 * Animation.hpp
 *
 *  Created on: Apr 25, 2019
 *      Author: nicop
 */

#ifndef COMPONENTS_ANIMATIONCOMPONENT_HPP_
#define COMPONENTS_ANIMATIONCOMPONENT_HPP_

// Streams
#include <iostream>

// Data structures
#include <map>
#include <string>

// Smart pointers
#include <memory>

// SFML libraries
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class AnimationComponent
{
public:
	// Constructor / Destructor
	explicit AnimationComponent(
			sf::Sprite& sprite,
			std::shared_ptr<sf::Texture> textureSheet
			);
	virtual ~AnimationComponent();

	// Functions
	void addAnimation(
			const std::string key,
			float animationTimer,
			std::vector<sf::IntRect>& rectVector
			);

	void play(const std::string key, const float& dt,
			const bool priority = false);
	void play(const std::string key, const float& dt,
			const float modifier, const bool priority = false);

	// Getters / Setters
	bool isDone(std::string key);

private:
	class Animation
	{
	public:
		explicit Animation(
				sf::Sprite& sprite,
				std::shared_ptr<sf::Texture> textureSheet,
				float animationTimer,
				const std::vector<sf::IntRect>& rectVector
				);
		virtual ~Animation();

		// Functions
		void play(const float& dt);
		void play(const float& dt, float modifier);
		void reset();

		// Getters / Setters
		bool isDone() const;

		// Resources
		sf::Sprite& sprite;
		std::shared_ptr<sf::Texture> textureSheet;
		std::vector<sf::IntRect> rectVector;

		// Variables
		std::size_t currentRect;
		float animationTimer;
		float timer;
		bool done;
	};

	sf::Sprite& sprite;
	std::shared_ptr<sf::Texture> textureSheet;
	std::map<std::string, std::shared_ptr<Animation>> animations;
	std::shared_ptr<Animation> lastAnimation;
	std::shared_ptr<Animation> priorityAnimation;
};

#endif /* COMPONENTS_ANIMATIONCOMPONENT_HPP_ */
