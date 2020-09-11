// 
// 
// 
#include "Sun.h"

Sun::Sun() :Object("Sun"){}

void Sun::update() {
	if (!(count = (++count) % rate))
		frame = (++frame) % frames;
}


void Sun::draw(Screen *screen) {
	
	for (int y = 0; y < length; y++) {
		for (int x = 0; x < width; x++) {
			if (pixels[frame][x][y] != 0) {
				screen->addPixel(x + _x, y + _y, r[pixels[frame][x][y] - 1], b[pixels[frame][x][y] - 1], g[pixels[frame][x][y] - 1]);
			}
		}
	}
}


