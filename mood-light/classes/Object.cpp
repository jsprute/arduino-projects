// 
// 
// 

#include "Object.h"


Object::Object(String name) {
	this->nextObject = 0;
	this->_x = 0;
	this->_y = 0;
	this->name = name;
}

void Object::set(int x, int y) {
	this->nextObject = 0;
	this->_x = x;
	this->_y = y;
}

void Object::draw(Screen* screen) {
	return;
}

void Object::update() {
	return;
}

int Object::getX() {
	return this->_x;
}

int Object::getY() {
	return this->_y;
}

void Object::move(int x, int y) {
	this->_x += x;
	this->_y += y;
}

boolean Object::active() {
	return false;
}

bool Object::isName(String name) {
	return this->name == name;
}

//int Object::phase(int _start, int _end, int _phase, int _max) {
//	return((_start * (_max - _phase) + _end * (_phase)) / _max);
//}

//uint32_t Object::createColor(int red, int green, int blue) {
//	return ((uint32_t)red << 16) + ((uint32_t)green << 8) + (uint32_t)blue;
//}
