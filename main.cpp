#include "SDL.h"
#include "SDL_image.h"
#include "global.h"
#include "uranium.h"
#include "neutron.h"
#include "simulation.h"
#include "general.h"

#include <iostream>
#include <time.h>


GlobalResources Global;

static SDL_Texture* LoadIMG(const char* filename) {
	auto s = IMG_Load(filename);
	if (s == nullptr) {
		std::cout << "IMG_Load: " << IMG_GetError() << std::endl;
		return nullptr;
	}
	
	auto t = SDL_CreateTextureFromSurface(Global.MainRenderer, s);
	
	if (t == nullptr) {
		std::cout << "SDL_CreateTextureFromSurface: " << SDL_GetError() << std::endl;
		return nullptr;
	}
	
	return t;
}


int main(int argc, char* argv[]) {
	
	//Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL Init: " << SDL_GetError() << std::endl;
        return 1;
    }
	
	//Initialize SDL_image
	if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0) {
		std::cout << "IMG Init: " << IMG_GetError() << std::endl;
	}
	
	//Initialize main window
	auto AppWindow = SDL_CreateWindow("Fission Simulation",
                               SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED,
							  SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
							  
    if (AppWindow == nullptr) {
        std::cout << "SDL_CreateWindow: " << SDL_GetError() << std::endl;
        return 1;
    }
	
	Global.MainRenderer = SDL_CreateRenderer(AppWindow, -1, SDL_RENDERER_ACCELERATED);
	
	if (Global.MainRenderer == nullptr) {
        std::cout << "SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        return 1;
    }
	
	SDL_RenderSetLogicalSize(Global.MainRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	
	Global.img_Uranium235 = LoadIMG("uranium235.png");
	Global.img_Uranium238 = LoadIMG("uranium238.png");
	Global.img_Neutron 	  = LoadIMG("neutron.png");
	
	std::list<Object*> __MainGroup;
	Global.MainGroup = &__MainGroup;
	
	std::list<Object*> __CQueue;
	Global.CreationQueue = &__CQueue;
	
	ResetSimulationMetrics();
	
	Global.Graph = false;
	
	srand (static_cast <unsigned> (time(0)));
	
	Simulation* MainSimulation = new Simulation();
	
	///////////////////////////////////// Main event loop /////////////////////////////////////
	bool Exit = false;
	while (!Exit) {
		
		///////////// Poll events ///////////// 
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					Exit = true;
				break;
			}
		}
		
		Global.KeyboardState = SDL_GetKeyboardState(NULL);
		
		//Clear screen
        SDL_SetRenderDrawColor(Global.MainRenderer, 0, 0, 0, 255);
        SDL_RenderClear(Global.MainRenderer);
		
		//draw playfield
		if (Global.Graph)
		{
			SDL_Rect R{0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
			SDL_SetRenderDrawColor(Global.MainRenderer, 20, 20, 20, 255);
			SDL_RenderFillRect(Global.MainRenderer, &R);
		}
		
		for(auto it = Global.MainGroup->begin(); it != Global.MainGroup->end(); ++it) {
			if (!(*it)->Destroyed) (*it)->Step();
			
		}
		
		for(auto it = Global.MainGroup->begin(); it != Global.MainGroup->end(); ) {
			auto next = it;
			std::advance(next,1);
			if ((*it)->Destroyed) Global.MainGroup->erase(it);
			it = next;
			
		}
		
		for(auto it = Global.CreationQueue->begin(); it != Global.CreationQueue->end(); it++) {
			Global.MainGroup->push_back(*it);
		}
		Global.CreationQueue->clear();

		if (Global.KeyboardState[SDL_SCANCODE_A]) {
			std::cout << "List size: " << Global.MainGroup->size() << std::endl;
		}
		
		if (MainSimulation->EndFlag) Exit = true;
		
		if (Global.Graph) {
			SDL_RenderPresent(Global.MainRenderer);
			SDL_Delay(16);
		}
		else {
			//SDL_Delay(1);
		}
	}
	
	IMG_Quit();
	SDL_Quit();
	
	return 0;
}