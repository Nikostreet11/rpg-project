/*
 * GraphicsSettings.cpp
 *
 *  Created on: May 24, 2019
 *      Author: nicop
 */

#include "GraphicsSettings.hpp"

// Constructor / Destructor
GraphicsSettings::GraphicsSettings()
{
	title = "DEFAULT";
	resolution = sf::VideoMode::getDesktopMode();
	fullscreen = false;
	verticalSync = false;
	framerateLimit = 120;
	contextSettings.antialiasingLevel = 0;
	videoModes = sf::VideoMode::getFullscreenModes();
}

GraphicsSettings::~GraphicsSettings()
{

}

// Functions
void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	if (ofs.is_open())
	{
		ofs << title;
		ofs << resolution.width << " " << resolution.height;
		ofs << fullscreen;
		ofs << framerateLimit;
		ofs << verticalSync;
		ofs << contextSettings.antialiasingLevel;
	}

	ofs.close();
}

void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> resolution.width >> resolution.height;
		ifs >> fullscreen;
		ifs >> framerateLimit;
		ifs >> verticalSync;
		ifs >> contextSettings.antialiasingLevel;
	}

	ifs.close();
}

