#include "simulation.h" 
#include "global.h"
#include "uranium.h"
#include "neutron.h"
#include "general.h"
#include <math.h>
#include <stdio.h>

Simulation::Simulation() : Object() {
	Iterations = MAX_ITERATIONS;
	BaseEnrichment = 1;
	Enrichment = BaseEnrichment;
	EndFlag = false;
	CSV_Index = 0;
}

void Simulation::FlushObjects() {
	for (auto it = Group->begin(); it != Group->end(); it++) {
		if ((*it)->id() != OBJ_SIMULATION) {
			(*it)->Destroyed = true;
		}
	}
}


const int Simulation::_scancodes[] = {
	SDL_SCANCODE_R,
	SDL_SCANCODE_SPACE
};

bool Simulation::KeyPressed(int key) {
	if (!PrevKeyState[key] && Global.KeyboardState[ _scancodes[key]] ) {
		return true;
	}
	
	return false;
	
}

void Simulation::Step() {
	
	Global.Simulation.TimeElapsed++;
	
	const int N_Atoms = 720;
	if (Global.Simulation.InitialFissionAtoms == 0) {
		FlushObjects();
		int FissionCount = (N_Atoms*Enrichment)/100;
		for (uint16_t k = 0; k < N_Atoms; k++) {
			bool Fissionable = true;
			if (FissionCount <= 0)
				Fissionable = false;
			new Uranium(unif(0, STAGE_WIDTH), unif(0, STAGE_HEIGHT),0,0, Fissionable);
			FissionCount--;
		}
		
		float angle = unif(0,2*M_PI);
		const float spd = 3;
		for (char ntn  = 0; ntn < 6; ntn++)
		new Neutron(STAGE_WIDTH/2, STAGE_HEIGHT/2, spd*cos(angle), spd*sin(angle));

	}
	
	bool FoundNeutron = false;
	for (char g = 0; g < 2; g++) {
		std::list<Object*>* ref = Global.MainGroup;
		if (g == 1) 
			std::list<Object*>* ref = Global.CreationQueue;
		
		for (auto it = ref->begin(); it != ref->end(); it++) {
			if ((*it)->id() == OBJ_NEUTRON) {
				FoundNeutron = true;
				break;
			}
		}
		
		if (FoundNeutron) break;
		
	}
	
	if (!FoundNeutron) { //check simulation end state
		if (Global.Simulation.FissionedAtoms > 0) {
			CSV_Metrics[CSV_Index] = { (float)Global.Simulation.FissionedAtoms / (float)Global.Simulation.InitialFissionAtoms,
									   (float)Global.Simulation.FissionedNeutrons / (float)Global.Simulation.GeneratedNeutrons,
											  Global.Simulation.TimeElapsed } ;
			CSV_Index++;
		}
		
		Iterations--;
		if (Iterations <= 0) {
			Iterations = MAX_ITERATIONS;
			
			//output file as enrich<n>.csv, where <n> is enrichment %
			char filename[30];
			sprintf(filename, "dump/enrich%u.csv\0", (unsigned int) Enrichment);
			FILE *file = fopen(filename, "w");
			
			if (file) {
				fputs("\"\",\"V1\",\"V2\",\"V3\"\n", file);
				printf("Dumping enrich%u with %u rows\n", (unsigned int) Enrichment, (unsigned int) CSV_Index);
				for (int k = 0; k < CSV_Index; k++) {
					char tmpStr[300];
					//"1",1,7
					sprintf(tmpStr, "\"%u\",%f,%f,%d\n",(unsigned int) k+1, CSV_Metrics[k].FissionedRatio, CSV_Metrics[k].CriticalValue, CSV_Metrics[k].TimeElapsed);
					
					fputs(tmpStr, file);
				}
				fclose(file);
				
			}
			
			Enrichment++;
			CSV_Index = 0;
		}
		
		if (Enrichment > 50) {
			EndFlag = true;
		}
		
		ResetSimulationMetrics();
		
	}

	
	for (uint8_t k = 0; k < _KEY_MAX; k++) {
		PrevKeyState[k] = Global.KeyboardState[ _scancodes[k] ];
	}
	
}

int Simulation::id() {return OBJ_SIMULATION;}