// Cloud.h

#ifndef _CLOUD_h
#define _CLOUD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#include "Object.h"
#else
	#include "WProgram.h"
#endif

class Cloud : public Object
{
public:
	Cloud();
	virtual void draw(Screen *screen);
	virtual void update();
private:
	const int length = 8;
	const int width = 3;

	const int frames = 1;
	const int rate = 25;

	int count = 0;
	int frame = 0;

	int r[1] = { 100 };
	int g[1] = { 100 };
	int b[1] = { 100 };

	int pixels[1][3][8] = {
		{
			{ 0,0,0,1,1,1,0,0 },
			{ 0,0,1,1,1,1,1,0 },
			{ 1,1,1,1,1,1,1,1 }
		}
	};

};

#endif

