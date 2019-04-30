/*
 * Component.h
 *
 *  Created on: Nov 1, 2018
 *      Author: Nikostreet11
 */

#ifndef SOURCE_COMPONENT_H_
#define SOURCE_COMPONENT_H_

class Component {
public:
	explicit Component(Component* parent = nullptr);
	virtual ~Component();

	virtual void addChild(Component* component) = 0;
	virtual bool removeChild(int index) = 0;
	virtual Component* getChild(int index) = 0;

	virtual void setParent(Component* parent);

private:
	Component* parent;
};

#endif /* SOURCE_COMPONENT_H_ */
