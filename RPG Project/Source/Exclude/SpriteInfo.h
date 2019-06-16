/*
 * SpriteInfo.h
 *
 *  Created on: Jul 31, 2018
 *      Author: nicop
 */

#ifndef EXCLUDE_SPRITEINFO_H_
#define EXCLUDE_SPRITEINFO_H_

#include "Exclude/Texture.h"

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

#endif /* EXCLUDE_SPRITEINFO_H_ */
