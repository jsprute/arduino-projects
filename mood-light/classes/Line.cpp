// 
// 
// 

#include "Line.h"

Line::Line() :Object("Line") {}

void Line::update() {
	if (!(count = (++count) % rate))
		frame = (++frame) % frames;
}


void Line::draw(Screen *screen) {

	for (int y = 0; y < length; y++) {
		for (int x = 0; x < width; x++) {
			if (pixels[frame][x][y] != 0) {
				screen->addPixel(x + _x, y + _y, r[pixels[frame][x][y] - 1], b[pixels[frame][x][y] - 1], g[pixels[frame][x][y] - 1]);
			}
		}
	}
}

void Line::updateColor(int r, int g, int b) {
	this->r[0] = r;
	this->g[0] = g;
	this->b[0] = b;

	return;
}
