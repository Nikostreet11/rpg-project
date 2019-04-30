/*
 * Item.h
 *
 *  Created on: Jul 20, 2018
 *      Author: Nikostreet11
 */

#ifndef ITEM_H_
#define ITEM_H_

#include <string>

class Item {
public:
	Item(std::string name, float weight);
	virtual ~Item();

private:
	std::string name;
	float weight;
};

#endif /* ITEM_H_ */
