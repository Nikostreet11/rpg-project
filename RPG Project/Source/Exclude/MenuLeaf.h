/*
 * MenuLeaf.h
 *
 *  Created on: Nov 6, 2018
 *      Author: nicop
 */

#ifndef SOURCE_MENULEAF_H_
#define SOURCE_MENULEAF_H_

#include "Exclude/MenuComponent.h"

class MenuContainer;
class MenuLeaf: public MenuComponent {
public:
	MenuLeaf(std::string name = "default_name");
	virtual ~MenuLeaf();

	virtual void action(MenuContainer* menu);
};

#endif /* SOURCE_MENULEAF_H_ */
