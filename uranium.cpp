#include "uranium.h"
#include "SDL.h"
#include "SDL_image.h"
#include "global.h"

Uranium::Uranium(float x, float y, float hs, float vs, bool Fissionable) :
x(x), y(y), hspeed(hs), vspeed(vs), Fissionable(Fissionable), Object() {
	
	if (Fissionable) {
		img = Global.img_Uranium235;
		Global.Simulation.InitialFissionAtoms++;
	}
	else
		img = Global.img_Uranium238;
	
	
}

void Uranium::Step() {
	
	x+=hspeed;
	y+=vspeed;
	
	if (Global.Graph) {
		SDL_Rect R{(int)x - size/2, (int)y - size/2, size, size};
		SDL_RenderCopy(Global.MainRenderer, img, NULL, &R);
	}
	
	if (Global.KeyboardState[SDL_SCANCODE_LEFT]) {
		Destroyed = true;
	}
	
	return;

}

bool Uranium::React() {
	if (Fissionable) {
		Destroyed = true;
		Global.Simulation.FissionedAtoms++;
		return true;
	}
	
	return false;
	
}

int Uranium::id() {return OBJ_URANIUM;}