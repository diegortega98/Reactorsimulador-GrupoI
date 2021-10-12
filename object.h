#ifndef _FISSION_OBJ_H
#define _FISSION_OBJ_H

#include <list>

enum OBJ_IDS {
	OBJ_URANIUM,
	OBJ_NEUTRON,
	OBJ_SIMULATION
};

class Object {
	public:
		virtual void Step() = 0;
		virtual int id() = 0;
		bool Destroyed;
		Object();
		
	
	protected:
		std::list<Object*>* Group;
	
	
};

#endif