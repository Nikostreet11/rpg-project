/*
 * Composite.h
 *
 *  Created on: Nov 1, 2018
 *      Author: Nikostreet11
 */

#ifndef SOURCE_COMPOSITE_H_
#define SOURCE_COMPOSITE_H_

#include <vector>
#include "Exclude/Component.h"

class Composite: public Component {
public:
	explicit Composite(Component* parent = nullptr);
	virtual ~Composite();

	virtual void addChild(Component* component);
	virtual bool removeChild(int index);
	virtual Component* getChild(int index);

private:
	std::vector<Component*> children;
};

#endif /* SOURCE_COMPOSITE_H_ */
