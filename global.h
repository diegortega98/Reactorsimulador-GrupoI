#ifndef _FISSION_GLOBAL_H
#define _FISSION_GLOBAL_H

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

#define STAGE_WIDTH  2000
#define STAGE_HEIGHT 2000

#include "SDL.h"
#include <list>


class Object;

typedef struct __GlobalResources {
	SDL_Texture* img_Uranium235;
	SDL_Texture* img_Uranium238;
	SDL_Texture* img_Neutron;
	SDL_Renderer* MainRenderer;
	std::list<Object*>* MainGroup;
	std::list<Object*>* CreationQueue;
	
	const uint8_t* KeyboardState;
	
	struct {
		int GeneratedNeutrons;
		int FissionedNeutrons; //to check for criticallity
		
		int InitialFissionAtoms;
		int FissionedAtoms; //to check for sustainable chain reaction
		
		int TimeElapsed;
		
	} Simulation;
	
	bool Graph;
	
} GlobalResources;

extern GlobalResources Global;

#endif