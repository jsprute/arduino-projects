
#include "box.h";

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define LED_INPUT 6
#define LEDI_INPUT 5
#define PIXEL_COUNT 110
#define PIXELI_COUNT 16
#define ACTION_PIN 8

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:

//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

//Adafruit_NeoPixel stripi = Adafruit_NeoPixel(PIXELI_COUNT, LEDI_INPUT, NEO_GRB + NEO_KHZ800);

int count = 0;
int resetCount = 0;

Box* inBox;
Box* outBox;

void setup() {

Serial.begin(9600);

//stripi.begin();
//stripi.show(); // Initialize all pixels to 'off'
//
//strip.begin();
//strip.show(); // Initialize all pixels to 'off'

pinMode(ACTION_PIN, INPUT);

randomSeed(analogRead(0));

resetCount = 0;

inBox = new Box(16,LEDI_INPUT);
outBox = new Box(110,LED_INPUT);

randomSeed(analogRead(0));

}


void loop() {
  
  Serial.println("Start of loop");
  
  int state = digitalRead(ACTION_PIN);
  
  uint16_t i, j;
  
  if(state && resetCount == 0){


    resetCount++;
  }

  inBox->addPixel(random(16), random(255),random(255),random(255));
  outBox->addPixel(random(110), random(255),random(255),random(255));
    
    
    
  delay(20);

  // allow time for the switch to fall back to 0
  if(resetCount > 0) resetCount++;
  if(resetCount > 1000) resetCount = 0;


  inBox->draw();
  outBox->draw();

  Serial.println("End of loop");
  
}



