/*
 * Subject.cpp
 *
 *  Created on: Jul 15, 2019
 *      Author: nicop
 */

#include "Subject.hpp"

Subject::Subject()
{
}

Subject::~Subject()
{
}

void Subject::attach(std::shared_ptr<Observer> observer)
{
	observers.push_back(observer);
}

void Subject::detach(std::shared_ptr<Observer> observer)
{
	observers.remove(observer);
}

void Subject::notify()
{
	for (auto& observer : observers)
	{
		observer->update();
	}
}
