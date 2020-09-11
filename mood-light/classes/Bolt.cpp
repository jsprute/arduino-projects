// 
// 
// 

#include "Bolt.h"

Bolt::Bolt() :Object("Bolt") {}

void Bolt::update() {

	int tempRate = rate;
	if (!frame) tempRate *= 4;

	if (!(count = (++count) % tempRate))
		frame = (++frame) % frames;
}


void Bolt::draw(Screen *screen) {

	for (int y = 0; y < length; y++) {
		for (int x = 0; x < width; x++) {
			if (pixels[frame][x][y] != 0) {
				screen->addPixel(x + _x, y + _y, r[pixels[frame][x][y] - 1], b[pixels[frame][x][y] - 1], g[pixels[frame][x][y] - 1]);
			}
		}
	}
}
