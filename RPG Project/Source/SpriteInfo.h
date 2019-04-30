/*
 * SpriteInfo.h
 *
 *  Created on: Jul 31, 2018
 *      Author: nicop
 */

#ifndef SPRITEINFO_H_
#define SPRITEINFO_H_

#include "Texture.h"

class SpriteInfo {
public:
	SpriteInfo();
	virtual ~SpriteInfo();

	void update(Texture texture, int posX, int posY, int width, int height);

	Texture getTexture() const;
	int getPosX() const;
	int getPosY() const;
	int getWidth() const;
	int getHeight() const;

private:
	Texture texture;
	int posX;
	int posY;
	int width;
	int height;
};

#endif /* SPRITEINFO_H_ */
