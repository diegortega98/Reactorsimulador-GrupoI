#ifndef _FISSION_SIMULATION_H
#define _FISSION_SIMULATION_H

#include "object.h" 

enum _KEY_INDEXES {
	_KEY_R = 0,
	_KEY_SPACE = 1,
	_KEY_MAX
	
};

struct DataRow {
	float FissionedRatio;
	float CriticalValue;
	int TimeElapsed;
};

class Simulation : public Object {
	public:
		static const int MAX_ITERATIONS = 1000;
		void Step();
		int id();
		Simulation();
		int Enrichment;
		int Iterations;
		int BaseEnrichment;
		bool EndFlag;
		DataRow CSV_Metrics[MAX_ITERATIONS];
		int CSV_Index;

	private:
		static const int _scancodes[];
		bool PrevKeyState[_KEY_MAX];
		void FlushObjects();
		bool KeyPressed(int key);
		
};



#endif