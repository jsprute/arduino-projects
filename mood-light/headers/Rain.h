// Rain.h

#ifndef _RAIN_h
#define _RAIN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "Object.h"
#else
	#include "WProgram.h"
#endif

class Rain : public Object
{
public:
	Rain();
	virtual void draw(Screen *screen);
	virtual void update();
private:
	const int length = 6;
	const int width = 4;

	const int frames = 6;
	const int rate = 25;

	int count = 0;
	int frame = 0;

	int r[1] = { 0 };
	int g[1] = { 0 };
	int b[1] = { 100 };

	int pixels[6][4][6] = {
		{
			{ 0,1,0,0,0,0 },
			{ 0,0,0,0,0,0 },
			{ 0,0,0,1,0,0 },
			{ 1,0,0,0,0,1 }
		},{
			{ 0,0,0,0,1,0 },
			{ 0,1,0,0,0,0 },
			{ 0,0,0,0,0,0 },
			{ 0,0,0,1,0,0 }
		},{
			{ 0,0,1,0,0,0 },
			{ 0,0,0,0,1,0 },
			{ 0,1,0,0,0,0 },
			{ 0,0,0,1,0,0 }
		},{
			{ 1,0,0,0,0,1 },
			{ 0,0,1,0,0,0 },
			{ 0,0,0,0,1,0 },
			{ 0,1,0,0,0,0 }
		},{
			{ 0,0,0,0,0,0 },
			{ 1,0,0,0,0,1 },
			{ 0,0,1,0,0,0 },
			{ 0,0,0,0,1,0 }
		},{
			{ 0,0,0,0,0,0 },
			{ 0,0,0,0,0,0 },
			{ 1,0,0,0,0,1 },
			{ 0,0,1,0,0,0 }
		}
	};

};


#endif

