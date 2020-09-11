
#include "Line.h"
//#include "Cloud.h"
//#include "Rain.h"
//#include "Bolt.h"
//#include "Moon.h"
//#include "Sun.h"
//#include "ObjectList.h"
#include "Object.h"
#include <Rainbowduino.h>
#include "Screen.h"

Screen* screen;
//Object* display = 0;


//ObjectList* activeObjects;
//ObjectList* objectPool;

//String input;   // for incoming serial data

Line* line1;
Line* line2;

int move = 4;

int targetRate = 35;
int currentRate = 0;

#define DST_IP "requestb.in"
//http://requestb.in/1cvj4d01

void setup()
{
	randomSeed(analogRead(6));

  /* add setup code here */
	screen = new Screen();
	screen->dim(20,3);
	
	line1 = new Line();
	
	line2 = new Line();
	

	//Sun* sun = new Sun();
	//sun->set(1, 1);

	//Moon* moon = new Moon();
	//moon->set(1, 1);

	//Bolt* bolt = new Bolt();
	//bolt->set(1, 1);

	//Cloud* cloud = new Cloud();
	//cloud->set(0, 2);

	//Rain* rain = new Rain();
	//rain->set(0, 4);

	//objectPool = new ObjectList();
	//objectPool->addObject(line1);
	//objectPool->addObject(moon);
	//objectPool->addObject(bolt);
	//objectPool->addObject(cloud);
	//objectPool->addObject(rain);
	

	//Set the speed for communicating with the ESP8266 module
	Serial.begin(115200);
}

void loop()
{
	
	//if (Serial.available() > 0) {
	//	input = Serial.readString();
	//	Serial.print("I received: ");
	//	Serial.println(input);
	//	display = objectPool->getObject(input);
	//}



	//if (display) {
	//	display->update();
	//	display->draw(screen);
	//}
	currentRate += 1;

	if (currentRate > targetRate) {
		move += 1;
		currentRate = 0;
	}

	if (move >= 6) {
		move = 0;


		line1->updateColor(random(255), random(255), random(255));
		line2->updateColor(random(255), random(255), random(255));
	}

	line1->set(3 - move, 0);
	line2->set(4 + move, 0);



	line1->update();
	line1->draw(screen);
	
	line2->update();
	line2->draw(screen);


	screen->draw();
	
	

	//input = "";
}


