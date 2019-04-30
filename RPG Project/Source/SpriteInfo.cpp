/*
 * SpriteInfo.cpp
 *
 *  Created on: Jul 31, 2018
 *      Author: nicop
 */

#include "SpriteInfo.h"

SpriteInfo::SpriteInfo() :
		texture(Texture::nullTexture),
		posX(-1),
		posY(-1),
		width(-1),
		height(-1) {}

SpriteInfo::~SpriteInfo() {}

void SpriteInfo::update(Texture texture, int posX, int posY, int width, int height) {
	this->texture = texture;
	this->posX = posX;
	this->posY = posY;
	this->width = width;
	this->height = height;
}

int SpriteInfo::getHeight() const {
	return height;
}

int SpriteInfo::getPosX() const {
	return posX;
}

int SpriteInfo::getPosY() const {
	return posY;
}

Texture SpriteInfo::getTexture() const {
	return texture;
}

int SpriteInfo::getWidth() const {
	return width;
}
