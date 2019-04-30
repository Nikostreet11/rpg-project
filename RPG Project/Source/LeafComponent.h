/*
 * LeafComponent.h
 *
 *  Created on: Nov 1, 2018
 *      Author: Nikostreet11
 */

#ifndef SOURCE_LEAFCOMPONENT_H_
#define SOURCE_LEAFCOMPONENT_H_

#include "Component.h"

class LeafComponent: public Component {
public:
	//LeafComponent();
	explicit LeafComponent(Component* parent = nullptr);
	virtual ~LeafComponent();

	virtual void addChild(Component* component);
	virtual bool removeChild(int index);
	virtual Component* getChild(int index);
};

#endif /* SOURCE_LEAFCOMPONENT_H_ */
