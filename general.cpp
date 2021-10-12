#include "general.h"
#include <math.h>
#include "global.h"

bool RadialCollision(float x1, float y1, float rad1, float x2, float y2, float rad2) {
	float distance = sqrt( powf(x1 - x2, 2) + powf(y1 - y2,2) );
	float rad = fmax(rad1, rad2);
	if (distance < rad) 
		return true;

	return false;
	
}

float unif(float low, float high) {
	float r = low + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(high - low)));
	return r;
}

int rsign() {
	if ((unsigned int)rand() % 2 == 0) {
		return 1;
	}
	return -1;
	
}

bool rbool(int p) {
	if ( ((unsigned int)rand() % 100) < p) {
		return true;
	}
	return false;
}

void ResetSimulationMetrics() {
	Global.Simulation.GeneratedNeutrons = 0;
	Global.Simulation.FissionedNeutrons = 0;  
	Global.Simulation.InitialFissionAtoms = 0;
	Global.Simulation.FissionedAtoms = 0;
	Global.Simulation.TimeElapsed = 0;
}