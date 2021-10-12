#include "neutron.h"
#include "general.h"
#include "uranium.h"
#include "global.h"
#include <math.h>

Neutron::Neutron(float x, float y, float hs, float vs) :
x(x), y(y), hspeed(hs), vspeed(vs), Object() {
	img = Global.img_Neutron;
	Global.Simulation.GeneratedNeutrons++;
}

void Neutron::Step() {
	
	x+=hspeed;
	y+=vspeed;
	
	if (Global.Graph) {
		SDL_Rect R{(int)x - size/2, (int)y - size/2, size, size};
		SDL_RenderCopy(Global.MainRenderer, img, NULL, &R);
	}
	
	for (auto it = Group->begin(); it != Group->end(); it++) {
		if ((*it)->id() == OBJ_URANIUM) {
			auto ur = dynamic_cast<Uranium*>(*it);
			if (RadialCollision(x, y, size, ur->x, ur->y, ur->size) && !ur->Destroyed) {
				Destroyed = true;
				if (ur->React()) {
					Global.Simulation.FissionedNeutrons++;
					char c_max = 2 + rand() % 2;
					for (char c = 0; c < c_max; c++) {
						
						float angle = unif(0,2*M_PI);
						const float spd = 3;
						new Neutron(x, y, spd*cos(angle), spd*sin(angle));
					}
				}
			}
		}
	}
	
	if (x < -20 || x > STAGE_WIDTH || y < -10 || y > STAGE_HEIGHT)
		Destroyed = true;
	
	
	return;

}

int Neutron::id() {return OBJ_NEUTRON;}