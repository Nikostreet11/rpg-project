/*
 * ServiceLocator.h
 *
 *  Created on: Sep 25, 2018
 *      Author: nicop
 */

#ifndef EXCLUDE_SERVICELOCATOR_H_
#define EXCLUDE_SERVICELOCATOR_H_

#include "Exclude/GraphicEngine.h"
#include "Exclude/GraphicService.h"
#include "Exclude/NullGraphicService.h"

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

#endif /* EXCLUDE_SERVICELOCATOR_H_ */
