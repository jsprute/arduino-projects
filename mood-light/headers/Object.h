// Object.h

#ifndef _OBJECT_h
#define _OBJECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "screen.h"
#else
	#include "WProgram.h"
#endif
class Object
{

public:
	Object *nextObject;
	Object(String name);
	virtual void draw(Screen* screen);
	virtual void update();
	virtual boolean active();
	virtual void set(int x, int y);
	int getX();
	int getY();
	void move(int x, int y);
	bool isName(String name);

protected:
	int _x;
	int _y;

private:
	String name;



};


#endif

