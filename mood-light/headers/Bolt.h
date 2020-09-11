// Bolt.h

#ifndef _BOLT_h
#define _BOLT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "Object.h"
#else
	#include "WProgram.h"
#endif

class Bolt : public Object
{
public:
	Bolt();
	virtual void draw(Screen *screen);
	virtual void update();
private:
	const int length = 4;
	const int width = 4;

	const int frames = 3;
	const int rate = 25;

	int count = 0;
	int frame = 0;

	int r[1] = { 100 };
	int g[1] = { 100 };
	int b[1] = { 0 };

	int pixels[3][4][4] = {
		{
			{ 0,0,0,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 }
		},{
			{ 0,0,1,1 },
			{ 0,0,1,0 },
			{ 0,0,0,0 },
			{ 0,0,0,0 }
		},{
			{ 0,0,1,1 },
			{ 0,0,1,0 },
			{ 0,1,0,0 },
			{ 1,0,1,0 }
		}
	};

};



#endif

