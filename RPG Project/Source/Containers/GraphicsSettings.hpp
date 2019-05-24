/*
 * GraphicsSettings.hpp
 *
 *  Created on: May 24, 2019
 *      Author: nicop
 */

#ifndef CONTAINERS_GRAPHICSSETTINGS_HPP_
#define CONTAINERS_GRAPHICSSETTINGS_HPP_

#include "pch.hpp"

class GraphicsSettings
{
public:
	// Constructor / Destructor
	GraphicsSettings();
	~GraphicsSettings();

	// Functions
	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);

	// Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool verticalSync;
	unsigned framerateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

};

#endif /* CONTAINERS_GRAPHICSSETTINGS_HPP_ */
