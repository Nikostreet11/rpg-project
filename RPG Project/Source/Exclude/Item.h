/*
 * Item.h
 *
 *  Created on: Jul 20, 2018
 *      Author: Nikostreet11
 */

#ifndef EXCLUDE_ITEM_H_
#define EXCLUDE_ITEM_H_

#include <string>

class Item {
public:
	Item(std::string name, float weight);
	virtual ~Item();

private:
	std::string name;
	float weight;
};

#endif /* EXCLUDE_ITEM_H_ */
