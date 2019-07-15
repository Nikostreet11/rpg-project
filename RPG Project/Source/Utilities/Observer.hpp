/*
 * Observer.hpp
 *
 *  Created on: Jul 15, 2019
 *      Author: nicop
 */

#ifndef UTILITIES_OBSERVER_HPP_
#define UTILITIES_OBSERVER_HPP_

#include "pch.hpp"

class Observer
{
public:
	Observer();
	virtual ~Observer();

	virtual void update() = 0;
};

#endif /* UTILITIES_OBSERVER_HPP_ */
