// Line.h

#ifndef _LINE_h
#define _LINE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
	#include "Object.h"
#else
	#include "WProgram.h"
#endif

class Line : public Object
{
public:
	Line();
	virtual void draw(Screen *screen);
	virtual void update();
	virtual void updateColor(int r, int g, int b);

private:
	const int length = 8;
	const int width = 1;

	const int frames = 1;
	const int rate = 25;

	int count = 0;
	int frame = 0;

	int r[1] = { 100 };
	int g[1] = { 100 };
	int b[1] = { 100 };

	int pixels[1][1][8] = { {{ 1,1,1,1,1,1,1,1 }} };
};

#endif

