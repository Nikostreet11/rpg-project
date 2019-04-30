/*
 * ServiceLocator.h
 *
 *  Created on: Sep 25, 2018
 *      Author: nicop
 */

#ifndef SERVICELOCATOR_H_
#define SERVICELOCATOR_H_

#include "GraphicService.h"
#include "GraphicEngine.h"
#include "NullGraphicService.h"

class ServiceLocator {
public:
	static void initialize();

	static void provideGraphicService(GraphicService* graphicService);
	static GraphicService* getGraphicService();

	// static void provideAudio(AudioService* audioService);
	// static AudioEngine& getAudioService();

private:
	ServiceLocator();
	virtual ~ServiceLocator();

	static GraphicService* graphicService;
	static NullGraphicService nullGraphicService;

	// static AudioService* audioService;
	// static NullAudioService nullAudioService;
};

#endif /* SERVICELOCATOR_H_ */
