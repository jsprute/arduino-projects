// 
// 
// 

#include "box.h"


Box::Box(int size, int pin) {

  strip = Adafruit_NeoPixel(size, pin, NEO_GRB + NEO_KHZ800);

  this->_size = size;
    this->_red = new int[size];
    this->_blue = new int[size];
    this->_green = new int[size];
    this->_phase = new int[size];
    

  // initialize all colors to 0
  for (int index = 0; index < size; index++) {
        this->_red[index] = 0;
        this->_blue[index] = 0;
        this->_green[index] = 0;
        this->_phase[index] = 0;
  }

  this->_dimAmount = 0;

  strip.begin();
  strip.show();

  return; 
}

void Box::draw() {
  // fade out the colors
  for(int i=0; i<strip.numPixels(); i++) {
    
    _phase[i] += 1;
    
    strip.setPixelColor(i, strip.Color(
      phase(_red[i],0,_phase[i],25),
      phase(_green[i],0,_phase[i],25), 
      phase(_blue[i],0,_phase[i],25)
      ));
      
  }
  
  strip.show();
  return;
}

void Box::dim(int amount, int rate) {
  
  this->_dimAmount = amount;
  this->_dimRate = rate;
  
  return;
}

void Box::addPixel(int x, int red, int blue, int green) {
  if ((x > (_size - 1)) || (x < 0)) return;
  
  this->_red[x] = red;
  this->_blue[x] = blue;
  this->_green[x] = green;
  this->_phase[x] = 0;
  
  return;
}

uint32_t Box::createColor(int red, int green, int blue) {
  return ((uint32_t)red << 16) + ((uint32_t)green << 8) + (uint32_t)blue;
}

int Box::phase(int _start, int _end, int _phase, int _max) {
            if(_phase > _max) _phase = _max;
  return((_start * (_max - _phase) + _end * (_phase)) / _max);
}
