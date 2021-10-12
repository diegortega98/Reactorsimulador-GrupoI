#ifndef _FISSION_NEUTRON_H
#define _FISSION_NEUTRON_H

#include "object.h"
#include "SDL.h"

class Neutron : public Object {
	public:
		float x;
		float y;
		float hspeed;
		float vspeed;
		const static int size  = 6;
		
		void Step();
		int id();
		
		Neutron(float x, float y, float hs, float vs);
		
	private:
		SDL_Texture* img;
	
};

#endif