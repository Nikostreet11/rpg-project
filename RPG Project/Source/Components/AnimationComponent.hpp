/*
 * Animation.hpp
 *
 *  Created on: Apr 25, 2019
 *      Author: nicop
 */

#ifndef COMPONENTS_ANIMATIONCOMPONENT_HPP_
#define COMPONENTS_ANIMATIONCOMPONENT_HPP_

#include "pch.hpp"

class AnimationComponent
{
public:
	// Constructor / Destructor
	explicit AnimationComponent(
			sf::Sprite& sprite,
			sf::Vector2u offset,
			sf::Vector2u size,
			sf::Vector2u spacing,
			std::shared_ptr<sf::Texture> textureSheet = nullptr);
	virtual ~AnimationComponent();

	// Functions
	void addAnimation(
			const std::string key,
			float animationTimer,
			std::vector<sf::Vector2u>& indexVector);

	void play(const std::string key, const float& dt,
			const bool priority = false);
	void play(const std::string key, const float& dt,
			const float modifier, const bool priority = false);
	void stop();

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
				std::vector<sf::Vector2u> indexVector,
				sf::Vector2u offset,
				sf::Vector2u size,
				sf::Vector2u spacing);
		virtual ~Animation();

		// Functions
		void play(const float& dt, float modifier);
		void reset();

		// Getters / Setters
		bool isDone() const;

		// Resources
		sf::Sprite& sprite;
		std::shared_ptr<sf::Texture> textureSheet;
		std::vector<sf::Vector2u> indexVector;

		// Variables
		sf::Vector2u offset;
		sf::Vector2u size;
		sf::Vector2u spacing;
		unsigned currentIndex;
		float animationTimer;
		float timer;
		bool done;
	};

	// Resources
	sf::Sprite& sprite;
	std::shared_ptr<sf::Texture> textureSheet;
	sf::Texture defaultTexture;
	sf::IntRect defaultTextureRect;

	std::map<std::string, std::shared_ptr<Animation>> animations;
	std::shared_ptr<Animation> lastAnimation;
	std::shared_ptr<Animation> priorityAnimation;

	// Variables
	sf::Vector2u offset;
	sf::Vector2u size;
	sf::Vector2u spacing;
};

#endif /* COMPONENTS_ANIMATIONCOMPONENT_HPP_ */
