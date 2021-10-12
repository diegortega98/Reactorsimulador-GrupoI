#include "object.h"
#include "global.h"

Object::Object() {
	Destroyed = false;
	Group = Global.MainGroup;
	Global.CreationQueue->push_back(this);
}