/*
 * GraphicsInfo.h
 *
 *  Created on: Jul 27, 2018
 *      Author: nicop
 */

#ifndef GRAPHICSINFO_H_
#define GRAPHICSINFO_H_

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

#endif /* GRAPHICSINFO_H_ */
