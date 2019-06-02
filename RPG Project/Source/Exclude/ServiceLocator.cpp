/*
 * ServiceLocator.cpp
 *
 *  Created on: Sep 25, 2018
 *      Author: nicop
 */

#include "Exclude/ServiceLocator.h"

GraphicService* ServiceLocator::graphicService = nullptr;
NullGraphicService ServiceLocator::nullGraphicService;

ServiceLocator::ServiceLocator() {}

ServiceLocator::~ServiceLocator() {}

void ServiceLocator::initialize() {
	graphicService = &nullGraphicService;
}

void ServiceLocator::provideGraphicService(GraphicService* graphicService) {
	if (graphicService == nullptr) {
		ServiceLocator::graphicService = &nullGraphicService;
	}
	else {
		ServiceLocator::graphicService = graphicService;
	}
}

GraphicService* ServiceLocator::getGraphicService() {
	return graphicService;
}

