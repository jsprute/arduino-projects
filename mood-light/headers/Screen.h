// screen.h
#ifndef _SCREEN_h
#define _SCREEN_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"

#else
	#include "WProgram.h"
#endif

class Screen {

private:
	int _red[8][8];
	int _blue[8][8];
	int _green[8][8];
	int _phase[8][8];
	int _dimAmount;
	int _dimRate;
	uint32_t createColor(int red, int green, int blue);

public:
	Screen();
	void draw();
	void dim(int amount, int rate);
	void addPixel(int x, int y, int red, int blue, int green);
	void addLine(int x1, int y1, int x2, int y2, int red, int blue, int green);
	int phase(int _start, int _end, int _phase, int _max);
};

#endif

