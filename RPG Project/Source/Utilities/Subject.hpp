/*
 * Subject.hpp
 *
 *  Created on: Jul 15, 2019
 *      Author: nicop
 */

#ifndef UTILITIES_SUBJECT_HPP_
#define UTILITIES_SUBJECT_HPP_

#include "pch.hpp"

#include "Observer.hpp"

class Subject
{
public:
	Subject();
	virtual ~Subject() = 0;

	virtual void attach(std::shared_ptr<Observer> observer);
	virtual void detach(std::shared_ptr<Observer> observer);
	virtual void notify();

private:
	std::list<std::shared_ptr<Observer>> observers;
};

#endif /* UTILITIES_SUBJECT_HPP_ */
