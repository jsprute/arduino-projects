// Sunny.h

#ifndef _SUN_h
#define _SUN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "Object.h"
#else
	#include "WProgram.h"
#endif

class Sun : public Object 
{
public:
	Sun();
	virtual void draw(Screen *screen);
	virtual void update();
private:
	const int length = 6;
	const int width = 6;

	const int frames = 3;
	const int rate = 25;
	
	int count = 0;
	int frame = 0;
	
	int r[1] = { 100 };
	int g[1] = { 100 };
	int b[1] = { 0 };

	int pixels[3][6][6] = {
		{
			{ 0,0,1,0,0,0 },
			{ 0,0,1,1,0,0 },
			{ 0,1,1,1,1,1 },
			{ 1,1,1,1,1,0 },
			{ 0,0,1,1,0,0 },
			{ 0,0,0,1,0,0 }
		},{
			{ 0,0,0,1,0,0 },
			{ 0,0,1,1,0,0 },
			{ 1,1,1,1,1,0 },
			{ 0,1,1,1,1,1 },
			{ 0,0,1,1,0,0 },
			{ 0,0,1,0,0,0 }
		},{
			{ 0,0,0,0,0,0 },
			{ 0,1,1,1,1,0 },
			{ 0,1,1,1,1,0 },
			{ 0,1,1,1,1,0 },
			{ 0,1,1,1,1,0 },
			{ 0,0,0,0,0,0 }
		}
	};

};


#endif

