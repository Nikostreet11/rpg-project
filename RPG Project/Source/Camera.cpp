/*
 * View.cpp
 *
 *  Created on: Jul 26, 2018
 *      Author: nicop
 */

#include "Camera.h"

Camera::Camera(int width, int height, int defaultShiftValue) :
		x(0), y(0),
		width(width), height(height),
		defaultShiftValue(defaultShiftValue) {}

Camera::~Camera() {}

void Camera::shift(Direction direction) {
	shift(direction, defaultShiftValue);
}

void Camera::shift(Direction direction, int shiftValue) {
	switch (direction) {
	case Direction::up:
		y -= shiftValue;
		break;
	case Direction::left:
		x -= shiftValue;
		break;
	case Direction::down:
		y += shiftValue;
		break;
	case Direction::right:
		x += shiftValue;
		break;
	case Direction::none:
		break;
	}
}

/*void Camera::shiftRight() {
	x += 1;
}

void Camera::shiftLeft() {
	x -= 1;
}

void Camera::shiftDown() {
	y += 1;
}

void Camera::shiftUp() {
	y -= 1;
}*/

int Camera::getHeight() const {
	return height;
}

int Camera::getWidth() const {
	return width;
}

int Camera::getX() const {
	return x;
}

int Camera::getY() const {
	return y;
}

void Camera::setDefaultShiftValue(int defaultShiftValue) {
	this->defaultShiftValue = defaultShiftValue;
}

void Camera::setX(int x) {
	this->x = x;
}

void Camera::setY(int y) {
	this->y = y;
}
