// Moon.h

#ifndef _MOON_h
#define _MOON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "Object.h"
#else
	#include "WProgram.h"
#endif
class Moon : public Object
{
public:
	Moon();
	virtual void draw(Screen *screen);
	virtual void update();
private:
	const int length = 6;
	const int width = 6;

	const int frames = 1;
	const int rate = 25;
	int count = 0;
	int frame = 0;


	int r[1] = { 0 };
	int g[1] = { 0 };
	int b[1] = { 100 };

	int pixels[1][6][6] = {
		{
			{ 0,0,1,1,1,0 },
			{ 0,1,1,0,0,0 },
			{ 1,1,0,0,0,0 },
			{ 1,1,0,0,0,0 },
			{ 0,1,1,0,0,0 },
			{ 0,0,1,1,1,0 }
		}
	};
};


#endif

