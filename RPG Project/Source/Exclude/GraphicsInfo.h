/*
 * GraphicsInfo.h
 *
 *  Created on: Jul 27, 2018
 *      Author: nicop
 */

#ifndef EXCLUDE_GRAPHICSINFO_H_
#define EXCLUDE_GRAPHICSINFO_H_

#include <string>

#include <SFML/Graphics.hpp>

class GraphicsInfo {
public:
	GraphicsInfo();
	virtual ~GraphicsInfo();

	sf::Texture texture;
	sf::Sprite sprite;
	std::string path;
};

#endif /* EXCLUDE_GRAPHICSINFO_H_ */
