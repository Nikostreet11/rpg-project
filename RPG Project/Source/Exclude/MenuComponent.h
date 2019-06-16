/*
 * MenuComponent.h
 *
 *  Created on: Nov 4, 2018
 *      Author: nicop
 */

#ifndef SOURCE_MENUCOMPONENT_H_
#define SOURCE_MENUCOMPONENT_H_

#include <string>

class MenuContainer;
class MenuComposite;
class MenuComponent {
public:
	explicit MenuComponent(std::string name = "default_name");
	virtual ~MenuComponent();

	/*virtual void addChild(MenuComponent* component) = 0;
	virtual bool removeChild(int index) = 0;
	virtual MenuComponent* getChild(int index) = 0;*/

	virtual void action(MenuContainer* menu) = 0;

	/*virtual void confirm(MenuContainer* menu) = 0;
	virtual void cancel(MenuContainer* menu) = 0;
	virtual void selectBackward() = 0;
	virtual void selectForward() = 0;*/

	const std::string& getName() const;
	void setName(const std::string& name);
	MenuComposite* getParent() const;
	void setParent(MenuComposite* parent);

protected:
	MenuComposite* parent;
	std::string name;
};

#endif /* SOURCE_MENUCOMPONENT_H_ */
