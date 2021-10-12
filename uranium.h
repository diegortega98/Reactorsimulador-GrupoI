#ifndef _FISSION_URANIUM_H
#define _FISSION_URANIUM_H

#include "object.h"
#include "SDL.h"

class Uranium : public Object {
	public:
		float x;
		float y;
		float hspeed;
		float vspeed;
		const static int size  = 16;
		bool Fissionable;
		
		void Step();
		int id();
		bool React();
		
		Uranium(float x, float y, float hs, float vs, bool Fissionable);
		
	private:
		SDL_Texture* img;
	
};

#endif