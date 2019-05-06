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
			/*sf::Vector2i startFrame,
			sf::Vector2i frames,
			sf::Vector2i size*/
			std::vector<sf::IntRect>& rectVector
			);

	void play(const std::string key, const float& dt);
	void play(const std::string key, const float& dt,
			const float modifier, const float modifierMax);

private:
	class Animation
	{
	public:
		explicit Animation(
				sf::Sprite& sprite,
				std::shared_ptr<sf::Texture> textureSheet,
				float animationTimer,
				/*sf::Vector2i startFrame,
				sf::Vector2i frames,
				sf::Vector2i size*/
				const std::vector<sf::IntRect>& rectVector
				);
		virtual ~Animation();

		// Functions
		void play(const float& dt);
		void play(const float& dt,
				const float modifier, const float modifierMax);
		void reset();

		// Variables
		sf::Sprite& sprite;
		std::shared_ptr<sf::Texture> textureSheet;
		float animationTimer;
		float timer;
		/*sf::Vector2i size;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;*/

		std::vector<sf::IntRect> rectVector;
		std::size_t currentRect;
	};

	sf::Sprite& sprite;
	std::shared_ptr<sf::Texture> textureSheet;
	std::map<std::string, std::shared_ptr<Animation>> animations;
	std::shared_ptr<Animation> lastAnimation;
};

#endif /* COMPONENTS_ANIMATIONCOMPONENT_HPP_ */
