/*
 * MenuContainer.h
 *
 *  Created on: Nov 4, 2018
 *      Author: nicop
 */

#ifndef SOURCE_MENUCONTAINER_H_
#define SOURCE_MENUCONTAINER_H_

#include <vector>
#include "Exclude/MenuComponent.h"
#include "Exclude/MenuComposite.h"

class MenuContainer {
public:
	MenuContainer();
	virtual ~MenuContainer();

	void addChild(MenuComponent* menuComponent);

	void confirm();
	void cancel();
	bool select(int index);
	bool selectBackward();
	bool selectForward();
	void resetActive();

	void returnToRoot();

	const MenuComponent& getComponent(int index) const;

	int getActive();
	MenuComposite& getCurrent() const;
	void setCurrent(MenuComposite* current);
	std::size_t getSize() const;

private:
	MenuComposite* root;
	MenuComposite* current;
};

#endif /* SOURCE_MENUCONTAINER_H_ */
