// box.h
#ifndef _BOX_h
#define _BOX_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#endif

#include <Adafruit_NeoPixel.h>


class Box {

private:
  Adafruit_NeoPixel strip;
  int* _red;
  int* _blue;
  int* _green;
  int* _phase;
  int _dimAmount;
  int _dimRate;
    int _size;
  uint32_t createColor(int red, int green, int blue);

public:
  Box(int size, int pin);
  void draw();
  void dim(int amount, int rate);
  void addPixel(int x, int red, int blue, int green, int speed, int death);
  int phase(int _start, int _end, int _phase, int _max);
};

#endif

