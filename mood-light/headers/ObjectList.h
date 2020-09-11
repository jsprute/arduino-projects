// ObjectList.h

#ifndef _OBJECTLIST_h
#define _OBJECTLIST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "Object.h"
#else
	#include "WProgram.h"
#endif


class ObjectList {
private:
	Object *root;
	Object *current;
	Object *previous;

public:
	ObjectList();
	void addObject(Object *object);
	Object* removeObject();
	Object* peekObject();
	Object* nextObject();
	Object* getObject(String name);
	void reset();
};



#endif

