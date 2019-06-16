/*
 * MenuComposite.h
 *
 *  Created on: Nov 4, 2018
 *      Author: nicop
 */

#ifndef SOURCE_MENUCOMPOSITE_H_
#define SOURCE_MENUCOMPOSITE_H_

#include <vector>
#include <string>
#include "Exclude/MenuComponent.h"

class MenuContainer;
class MenuComposite: public MenuComponent {
public:
	explicit MenuComposite(std::string name = "default_name");
	virtual ~MenuComposite();

	void addChild(MenuComponent* component);
	bool removeChild(int index);
	MenuComponent* getChild(int index);
	bool isRoot() const;

	virtual void action(MenuContainer* menu);

	void confirm(MenuContainer* menu);
	void cancel(MenuContainer* menu);
	bool select(int index);
	bool selectBackward();
	bool selectForward();
	void resetActive();

	int getActive() const;
	std::size_t getSize() const;

private:
	std::vector<MenuComponent*> children;
	int active;
	static const int NO_ACTIVE = -1; // must be < 0
};

#endif /* SOURCE_MENUCOMPOSITE_H_ */
