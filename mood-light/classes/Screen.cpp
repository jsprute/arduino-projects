// 
// 
// 

#include "Screen.h"
#include <Rainbowduino.h>


Screen::Screen() {
	
	// initialize all colors to 0
	for (int index = 0; index < 8; index++) {
		for (int index2 = 0; index2 < 8; index2++) {
			this->_red[index][index2] = 0;
			this->_blue[index][index2] = 0;
			this->_green[index][index2] = 0;
			this->_phase[index][index2] = 0;
		}
	}

	this->_dimAmount = 0;
	
	Rb.init();

}

void Screen::draw() {
	
	static int rateCount = 0;

	rateCount++;
	boolean dimIt = this->_dimRate < rateCount;
	if (dimIt) rateCount = 0;

	for (int index = 0; index < 8; index++) {
		for (int index2 = 0; index2 < 8; index2++) {

			if (this->_dimAmount > 0 && this->_phase[index][index2] < this->_dimAmount && dimIt) {
				this->_phase[index][index2] += 1;
				if (this->_phase[index][index2] > this->_dimAmount) {
					this->_phase[index][index2] = this->_dimAmount;
				}
			}

			if (this->_phase[index][index2] <= this->_dimAmount) {
				Rb.setPixelXY(index, index2,
					createColor(
						phase(this->_red[index][index2], 0, this->_phase[index][index2], this->_dimAmount),
						phase(this->_green[index][index2], 0, this->_phase[index][index2], this->_dimAmount),
						phase(this->_blue[index][index2], 0, this->_phase[index][index2], this->_dimAmount)));
			}

		}
	}

	

	return;
}

void Screen::dim(int amount, int rate) {
	this->_dimAmount = amount;
	this->_dimRate = rate;
	return;
}

void Screen::addPixel(int x, int y, int red, int blue, int green) {
	if (x > 7 || x < 0) return;
	if (y > 7 || y < 0) return;
	
	this->_red[x][y] = red;
	this->_blue[x][y] = blue;
	this->_green[x][y] = green;
	this->_phase[x][y] = 0;
	
	return;
}

void Screen::addLine(int x1, int y1, int x2, int y2, int red, int blue, int green) {
	return;
}

uint32_t Screen::createColor(int red, int green, int blue) {
	return ((uint32_t)red << 16) + ((uint32_t)green << 8) + (uint32_t)blue;
}

int Screen::phase(int _start, int _end, int _phase, int _max) {
	return((_start * (_max - _phase) + _end * (_phase)) / _max);
}