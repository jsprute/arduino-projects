#include <RGBConverter.h>
#include <Rainbowduino.h>

/*
Rainbowduino v3.0 Library examples:

Print Shapes on 2D plane (8x8 matrix)

*/



#define LIGHTVALUE 3
#define LIGHTTRIGGER 2
#define BRAKESENSE 3
#define LEFTBUTTON 6
#define RIGHTBUTTON 7
#define MIDSTATE 500


int default_anim = 0;
int stop_anim = 0;
int turn_anim = 0;

int _line = 0;

boolean leftOn;
boolean rightOn;
boolean leftDown;
boolean rightDown;

boolean breakDown;
boolean breakOn;

int counter;
int delayCounter;

boolean anim_reset = true;
int anim_old = 0;
int anim_value = 0;

int timerTracker = 0;
int timeDelay = 100;

int blink_delay = 0;
int blink_interval = 500;
boolean blink_state = LOW;


void setup()
{
	// comment
	//Serial.begin(9600);

	Rb.init();
	pinMode(LIGHTVALUE, OUTPUT);
	pinMode(LIGHTTRIGGER, OUTPUT);


	leftOn = false;
	rightOn = false;
	leftDown = true;
	rightDown = true;
	breakDown = true;
	breakOn = false;


	_line = 0;

	anim_reset = true;
	anim_old = 0;
	anim_value = 0;
	BothOff();

}

unsigned char x, y, z;

void loop()
{

	//////////////////////////////
	// Read Inputs
	int brakeState = analogRead(BRAKESENSE);
	int leftState = analogRead(LEFTBUTTON);
	int rightState = analogRead(RIGHTBUTTON);

	// leftValue 0 = unpressed
	// leftValue 1 = pressed
	// rightValue 0 = unpressed
	// rightValue 1 = pressed
	// brakeValue 1 = unpressed
	// brakeValue 0 = pressed

	//////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////
	// Logic for inputs

	///////////////////////////////////////////////////////////
	/// LEFT
	if (!rightDown)
	{
		if (pressed(leftState) && !leftDown && !leftOn)
		{
			leftOn = true;
			leftDown = true;
			delayCounter = 0;
			rightDown = false;
			rightOn = false;
			anim_reset = true;
		}

		if (pressed(leftState) && !leftDown && leftOn)
		{
			leftOn = false;
			leftDown = true;
			delayCounter = 0;
			BothOff();
			anim_reset = true;
		}


		if (!pressed(leftState) && leftDown)
		{
			leftDown = false;
		}
	}

	//////////////////////////////////////////////////////////////
	// Right

	if (!leftDown)
	{
		if (pressed(rightState) && !rightDown && !rightOn)
		{
			rightOn = true;
			rightDown = true;
			delayCounter = 0;
			leftDown = false;
			leftOn = false;
			anim_reset = true;
		}

		if (pressed(rightState) && !rightDown && rightOn)
		{
			rightOn = false;
			rightDown = true;
			delayCounter = 0;
			BothOff();
			anim_reset = true;
		}

		if (!pressed(rightState) && rightDown)
		{
			rightDown = false;
		}
	}
	///////////////////////////////////////////////////////////////////
	// CYCLE THROUGH THEMES

	if (rightDown && !leftDown && pressed(leftState))
	{
		leftDown = true;
	}

	if (rightDown && leftDown && !pressed(leftState))
	{
		anim_value += 1;
		if (anim_value > 2)
			anim_value = 0;

		anim_reset = true;
		leftDown = false;
	}



	////////////////////////////////////////////////////////////////////
	// BREAK

	if (!pressed(brakeState) && breakOn == false)
	{
		breakOn = true;
		breakDown = true;
		delayCounter = 0;
		anim_reset = true;
	}
	else if (pressed(brakeState) && breakOn == true)
	{
		breakOn = false;
		breakDown = false;
		delayCounter = 0;
		breakDown = false;
		anim_reset = true;
	}

	//////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////
	// Handling hand signals

	//int blink_delay = 0;
	//int blink_interval = 1000;
	//boolean blink_state = LOW;

	blink_delay += 1;
	if (blink_delay > blink_interval)
	{
		blink_delay = 0;
		blink_state = !blink_state;

		if (blink_state){
			if (leftOn)
			{
				LeftOn();
			}

			if (rightOn)
			{
				RightOn();
			}

		}
		else{
			BothOff();
		}


	}

	//////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////
	// Animation Code
	if (breakOn)
	{
		switch (anim_value){
		case 0:
			FadeSwipeBreak();
			break;
		case 1:
			MusicStopBeatAnim();
			break;
		case 2:
			SquareItBrakeDefault();
			break;
		}
	}
	else if (leftOn && !rightOn)
	{
		switch (anim_value){
		case 0:
			left_Signal();
			break;
		case 1:
			MusicLeftBeatAnim();
			break;
		case 2:
			SquareItLeftDefault();
			break;
		}
	}
	else if (!leftOn && rightOn)
	{
		switch (anim_value){
		case 0:
			right_Signal();
			break;
		case 1:
			MusicRightBeatAnim();
			break;
		case 2:
			SquareItRightDefault();
			break;
		}
	}
	else
	{

		switch (anim_value){
		case 0:
			FadeSwipeDefault();
			break;
		case 1:
			MusicBeatAnim();
			break;
		case 2:
			SquareItDefault();
			break;
		}
	}

	// End Animation
	////////////////////////////////////////////////////////      

	/*
	Serial.print("L On: ");
	Serial.print(leftOn);
	Serial.print("  R On:");
	Serial.println(rightOn);
	*/



}

boolean pressed(int state)
{
	return state > MIDSTATE;
}

void clearScreen()
{
	Rb.blankDisplay();
	return;
}

//define LIGHTVALUE 2
//define LIGHTTRIGGER 3

void LeftOn()
{
	digitalWrite(LIGHTVALUE, HIGH);
	digitalWrite(LIGHTTRIGGER, HIGH);
	digitalWrite(LIGHTTRIGGER, LOW);
	digitalWrite(LIGHTVALUE, LOW);
	digitalWrite(LIGHTTRIGGER, HIGH);
	digitalWrite(LIGHTTRIGGER, LOW);
}

void RightOn()
{
	digitalWrite(LIGHTVALUE, HIGH);
	digitalWrite(LIGHTTRIGGER, HIGH);
	digitalWrite(LIGHTTRIGGER, LOW);
	digitalWrite(LIGHTVALUE, LOW);
}

void BothOff()
{
	digitalWrite(LIGHTVALUE, LOW);
	digitalWrite(LIGHTTRIGGER, HIGH);
	digitalWrite(LIGHTTRIGGER, LOW);
	digitalWrite(LIGHTTRIGGER, HIGH);
	digitalWrite(LIGHTTRIGGER, LOW);

}

/*
0,0


7,7

*/



//  Rb.setPixelXY(0, 0, 255, 0, 0);  // red
//  Rb.setPixelXY(7, 7, 0, 255, 0);  // Green
//  Rb.setPixelXY(0, 7, 0, 0, 255);  // blue
// animations
void FadeSwipeDefault()
{
	static int yCord = 0;
	static int intCount = 0;
	static boolean downDir = true;
	int        intDelay = 100;
	static int tailArray[] = { 0, 0, 0, 0, 0 };
	if (anim_reset)
	{
		clearScreen();
		anim_reset = false;
		yCord = 0;
		intCount = 0;
		downDir = true;
		for (int index = 0; index < 5; index += 1)
			tailArray[index] = 0;
	}
	intCount += 1;

	if (intCount > intDelay)
	{
		intCount = 0;
		if (downDir)
			yCord += 1;
		else
			yCord -= 1;

		for (int index = 3; index >= 0; index -= 1)
			tailArray[index + 1] = tailArray[index];

		tailArray[0] = yCord;

		for (int index = 4; index >= 0; index -= 1)
		{
			switch (index)
			{
			case 4:
				drawLine(((uint32_t)0), 0, tailArray[index], 7, tailArray[index]);
				break;
			case 3:
				drawLine(((uint32_t)(35) << 16) + ((uint32_t)(35) << 8), 0, tailArray[index], 7, tailArray[index]);
				break;
			case 2:
				drawLine(((uint32_t)(70) << 16) + ((uint32_t)(70) << 8), 0, tailArray[index], 7, tailArray[index]);
				break;
			case 1:
				drawLine(((uint32_t)(130) << 16) + ((uint32_t)(35) << 8), 0, tailArray[index], 7, tailArray[index]);
				break;
			case 0:
				drawLine(((uint32_t)(255) << 16) + ((uint32_t)(0) << 8), 0, tailArray[index], 7, tailArray[index]);
				break;
			}
		}

		if (yCord <= -2 && downDir == false)
			downDir = true;
		else if (yCord >= 9 && downDir == true)
			downDir = false;
	}
}


void FadeSwipeBreak()
{
	static int yCord = 0;
	static int intCount = 0;
	static boolean downDir = true;
	int        intDelay = 100;
	static int tailArray[] = { 0, 0, 0 };

	if (anim_reset)
	{
		clearScreen();
		anim_reset = false;
		yCord = 0;
		intCount = 0;
		downDir = true;
		for (int index = 0; index < 3; index += 1)
			tailArray[index] = 0;
	}

	intCount += 1;

	if (intCount > intDelay)
	{
		intCount = 0;
		if (downDir)
			yCord += 1;
		else
			yCord -= 1;

		for (int index = 1; index >= 0; index -= 1)
			tailArray[index + 1] = tailArray[index];

		tailArray[0] = yCord;

		for (int index = 2; index >= 0; index -= 1)
		{
			switch (index)
			{
			case 2:
				drawLine(0, tailArray[index], 0, tailArray[index], 7);
				drawLine(0, 7 - tailArray[index], 0, 7 - tailArray[index], 7);
				break;
			case 1:
				drawLine(((uint32_t)(70) << 16), tailArray[index], 0, tailArray[index], 7);
				drawLine(((uint32_t)(70) << 16), 7 - tailArray[index], 0, 7 - tailArray[index], 7);
				break;
			case 0:
				drawLine(((uint32_t)(255) << 16), tailArray[index], 0, tailArray[index], 7);
				drawLine(((uint32_t)(255) << 16), 7 - tailArray[index], 0, 7 - tailArray[index], 7);
				break;
			}
		}

		if (yCord <= 0 && downDir == false)
			downDir = true;
		else if (yCord >= 3 && downDir == true)
			downDir = false;
	}
}

void left_Signal()
{
	static int yCord = 0;
	static int intCount = 0;
	int        intDelay = 100;
	static int tailArray[] = { 0, 0, 0, 0, 0 };

	if (anim_reset)
	{
		clearScreen();
		anim_reset = false;
		yCord = -4;
		intCount = 0;
		for (int index = 0; index < 5; index += 1)
			tailArray[index] = -4;
	}

	intCount += 1;

	if (intCount > intDelay)
	{
		intCount = 0;

		yCord += 1;

		for (int index = 3; index >= 0; index -= 1)
			tailArray[index + 1] = tailArray[index];

		tailArray[0] = yCord;

		for (int index = 4; index >= 0; index -= 1)
		{
			switch (index)
			{
			case 4:
				drawLine(0, tailArray[index], 0, tailArray[index] + 3, 3);
				drawLine(0, tailArray[index], 7, tailArray[index] + 3, 4);
				break;
			case 3:
				drawLine(((uint32_t)(35) << 16) + ((uint32_t)(35) << 8), tailArray[index], 0, tailArray[index] + 3, 3);
				drawLine(((uint32_t)(35) << 16) + ((uint32_t)(35) << 8), tailArray[index], 7, tailArray[index] + 3, 4);
				break;
			case 2:
				drawLine(((uint32_t)(70) << 16) + ((uint32_t)(70) << 8), tailArray[index], 0, tailArray[index] + 3, 3);
				drawLine(((uint32_t)(70) << 16) + ((uint32_t)(70) << 8), tailArray[index], 7, tailArray[index] + 3, 4);
				break;
			case 1:
				drawLine(((uint32_t)(135) << 16) + ((uint32_t)(135) << 8), tailArray[index], 0, tailArray[index] + 3, 3);
				drawLine(((uint32_t)(135) << 16) + ((uint32_t)(135) << 8), tailArray[index], 7, tailArray[index] + 3, 4);
				break;
			case 0:
				drawLine(((uint32_t)(255) << 16) + ((uint32_t)(255) << 8), tailArray[index], 0, tailArray[index] + 3, 3);
				drawLine(((uint32_t)(255) << 16) + ((uint32_t)(255) << 8), tailArray[index], 7, tailArray[index] + 3, 4);
				break;
			}
		}

		//    if(yCord <= 0 && downDir == false)
		//      downDir = true;
		// else
		if (yCord >= 12)
			yCord = -4;
	}
}

void right_Signal()
{
	static int yCord = 0;
	static int intCount = 0;
	int        intDelay = 100;
	static int tailArray[] = { 0, 0, 0, 0, 0 };

	if (anim_reset)
	{
		clearScreen();
		anim_reset = false;
		yCord = 12;
		intCount = 0;
		for (int index = 0; index < 5; index += 1)
			tailArray[index] = 12;
	}

	intCount += 1;

	if (intCount > intDelay)
	{
		intCount = 0;
		yCord -= 1;

		for (int index = 3; index >= 0; index -= 1)
			tailArray[index + 1] = tailArray[index];

		tailArray[0] = yCord;

		for (int index = 4; index >= 0; index -= 1)
		{
			switch (index)
			{
			case 4:
				drawLine(0, tailArray[index], 0, tailArray[index] - 3, 3);
				drawLine(0, tailArray[index], 7, tailArray[index] - 3, 4);
				break;
			case 3:
				drawLine(((uint32_t)(35) << 16) + ((uint32_t)(35) << 8), tailArray[index], 0, tailArray[index] - 3, 3);
				drawLine(((uint32_t)(35) << 16) + ((uint32_t)(35) << 8), tailArray[index], 7, tailArray[index] - 3, 4);
				break;
			case 2:
				drawLine(((uint32_t)(70) << 16) + ((uint32_t)(70) << 8), tailArray[index], 0, tailArray[index] - 3, 3);
				drawLine(((uint32_t)(70) << 16) + ((uint32_t)(70) << 8), tailArray[index], 7, tailArray[index] - 3, 4);
				break;
			case 1:
				drawLine(((uint32_t)(135) << 16) + ((uint32_t)(135) << 8), tailArray[index], 0, tailArray[index] - 3, 3);
				drawLine(((uint32_t)(135) << 16) + ((uint32_t)(135) << 8), tailArray[index], 7, tailArray[index] - 3, 4);
				break;
			case 0:
				drawLine(((uint32_t)(255) << 16) + ((uint32_t)(255) << 8), tailArray[index], 0, tailArray[index] - 3, 3);
				drawLine(((uint32_t)(255) << 16) + ((uint32_t)(255) << 8), tailArray[index], 7, tailArray[index] - 3, 4);
				break;
			}
		}

		//    if(yCord <= 0 && downDir == false)
		//      downDir = true;
		// else
		if (yCord <= -4)
			yCord = 12;
	}

}


void MusicBeatAnim()
{
	static int beatCount = 0;
	int beatDelay = 1000;
	static int animCount = 0;
	int animDelay = 50;

	static int height[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	static uint32_t colors[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	beatCount += 1;
	animCount += 1;

	if (anim_reset)
	{
		clearScreen();
		anim_reset = false;

		beatCount = beatDelay;
		animCount = 0;

	}

	if (beatCount >= beatDelay)
	{
		for (int index = 0; index < 8; index++){
			height[index] = random(1, 9);
			colors[index] = (uint32_t)((uint32_t)(random(5, 120)) << 16) +
				(uint32_t)((random(5, 120)) << 8) +
				(uint32_t)(random(5, 120));
		}

		beatCount = 1;
	}

	if (animCount > animDelay)
	{
		for (int index = 0; index < 8; index++)
		{
			if (beatCount < beatDelay / 2)
			{
				//        Serial.print("UP: ");
				//        Serial.println((unsigned char)(((beatDelay*height[index]))/(beatDelay-beatCount)));
				Rb.setPixelXY((unsigned char)index,
					(unsigned char)(8 - ((int)(float)beatCount / ((float)beatDelay / 2.0))*height[index]),
					colors[index]);
			}
			else
			{
				//        Serial.print("DN: ");
				//        Serial.println((unsigned char)(((beatDelay*height[index]))/(beatCount)));
				Rb.setPixelXY((unsigned char)index,
					(unsigned char)(8 - ((int)(float)(beatDelay - beatCount) / ((float)beatDelay / 2.0))*height[index]),
					(uint32_t)0);
			}
		}
		animCount = 0;
	}

}

void MusicLeftBeatAnim()
{
	static int beatCount = 0;
	int beatDelay = 1000;
	static int animCount = 0;
	int animDelay = 50;

	static int height[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	static uint32_t colors[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	beatCount += 1;
	animCount += 1;

	if (anim_reset)
	{
		clearScreen();
		anim_reset = false;

		beatCount = beatDelay;
		animCount = 0;

	}

	if (beatCount >= beatDelay)
	{
		for (int index = 0; index < 8; index++){
			if (index < 4)
				height[index] = random(1 + index, 2 + index * 2);
			else
				height[index] = random(1 + (8 - index), 2 + (8 - index) * 2);

			colors[index] = (uint32_t)((uint32_t)(random(100, 200)) << 16) +
				(uint32_t)((random(100, 200)) << 8);
		}

		beatCount = 1;
	}

	if (animCount > animDelay)
	{
		for (int index = 0; index < 8; index++)
		{
			if (beatCount < beatDelay / 2)
			{
				//        Serial.print("UP: ");
				//        Serial.println((unsigned char)(((beatDelay*height[index]))/(beatDelay-beatCount)));
				Rb.setPixelXY(
					(unsigned char)(((int)(float)beatCount / ((float)beatDelay / 2.0))*height[index]),
					(unsigned char)index,
					colors[index]);
			}
			else
			{
				//        Serial.print("DN: ");
				//        Serial.println((unsigned char)(((beatDelay*height[index]))/(beatCount)));
				Rb.setPixelXY(
					(unsigned char)(((int)(float)(beatCount - beatDelay / 2) / ((float)beatDelay / 2.0))*height[index]),
					(unsigned char)index,
					(uint32_t)0);
			}
		}
		animCount = 0;
	}

}

void MusicRightBeatAnim()
{
	static int beatCount = 0;
	int beatDelay = 1000;
	static int animCount = 0;
	int animDelay = 50;

	static int height[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	static uint32_t colors[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	beatCount += 1;
	animCount += 1;

	if (anim_reset)
	{
		clearScreen();
		anim_reset = false;

		beatCount = beatDelay;
		animCount = 0;

	}

	if (beatCount >= beatDelay)
	{
		for (int index = 0; index < 8; index++){
			if (index < 4)
				height[index] = random(1 + index, 2 + index * 2);
			else
				height[index] = random(1 + (8 - index), 2 + (8 - index) * 2);



			colors[index] = (uint32_t)((uint32_t)(random(100, 200)) << 16) +
				(uint32_t)((random(100, 200)) << 8);
		}

		beatCount = 1;
	}

	if (animCount > animDelay)
	{
		for (int index = 0; index < 8; index++)
		{
			if (beatCount < beatDelay / 2)
			{
				//        Serial.print("UP: ");
				//        Serial.println((unsigned char)(((beatDelay*height[index]))/(beatDelay-beatCount)));
				Rb.setPixelXY(
					(unsigned char)(8 - ((int)(float)beatCount / ((float)beatDelay / 2.0))*height[index]),
					(unsigned char)index,
					colors[index]);
			}
			else
			{
				//        Serial.print("DN: ");
				//        Serial.println((unsigned char)(((beatDelay*height[index]))/(beatCount)));
				Rb.setPixelXY(
					(unsigned char)(8 - ((int)(float)(beatCount - beatDelay / 2) / ((float)beatDelay / 2.0))*height[index]),
					(unsigned char)index,
					(uint32_t)0);
			}
		}
		animCount = 0;
	}

}

void MusicStopBeatAnim()
{
	static int beatCount = 0;
	int beatDelay = 500;
	static int animCount = 0;
	int animDelay = 50;

	static int height[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	static uint32_t colors[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	beatCount += 1;
	animCount += 1;

	if (anim_reset)
	{
		clearScreen();
		anim_reset = false;

		beatCount = beatDelay;
		animCount = 0;

	}

	if (beatCount >= beatDelay)
	{
		for (int index = 0; index < 8; index++){
			height[index] = random(1, 6);
			colors[index] = (uint32_t)((uint32_t)(200) << 16);
		}

		beatCount = 1;
	}

	if (animCount > animDelay)
	{
		for (int index = 0; index < 8; index++)
		{
			if (beatCount < beatDelay / 2)
			{
				//        Serial.print("UP: ");
				//        Serial.println((unsigned char)(((beatDelay*height[index]))/(beatDelay-beatCount)));
				Rb.setPixelXY((unsigned char)index,
					(unsigned char)(8 - ((int)(float)beatCount / ((float)beatDelay / 2.0))*height[index]),
					colors[index]);

				Rb.setPixelXY((unsigned char)index,
					(unsigned char)(((int)(float)beatCount / ((float)beatDelay / 2.0))*height[7 - index]),
					colors[index]);
			}
			else
			{
				//        Serial.print("DN: ");
				//        Serial.println((unsigned char)(((beatDelay*height[index]))/(beatCount)));
				Rb.setPixelXY((unsigned char)index,
					(unsigned char)(8 - ((int)(float)(beatDelay - beatCount) / ((float)beatDelay / 2.0))*height[index]),
					(uint32_t)0);

				Rb.setPixelXY((unsigned char)index,
					(unsigned char)(((int)(float)(beatDelay - beatCount) / ((float)beatDelay / 2.0))*height[7 - index]),
					(uint32_t)0);

			}
		}
		animCount = 0;
	}

}


void SquareItDefault()
{
	static int squareCount = 0;
	static int animCount = 0;
	static int colors[3] = { 0, 0, 0 };
	int animDelay = 150;
	int squareInterval = 7;

	static uint32_t squares[4] = { (uint32_t)0, (uint32_t)0, (uint32_t)0, (uint32_t)0 };

	if (anim_reset)
	{
		clearScreen();
		anim_reset = false;
		for (int index = 0; index < 4; index++)
			squares[index] = (uint32_t)0;

		for (int index = 0; index < 3; index++)
			colors[index] = 0;

		animCount = 100;
	}

	animCount++;
	if (animCount > animDelay)
	{
		animCount = 0;
		squareCount++;

		for (int index = 3; index >= 0; index--)
		{
			squares[index + 1] = squares[index];
		}

		if (squareCount >= squareInterval)
		{
			colors[0] = random(5, 100);
			colors[1] = random(5, 100);
			colors[2] = random(5, 100);

			squares[0] = (uint32_t)((uint32_t)(colors[0]) << 16) +
				(uint32_t)((colors[1]) << 8) +
				(uint32_t)(colors[2]);

			for (int index = 0; index < 3; index++)
				colors[index] = colors[index] / 3;
			squareCount = 0;
		}
		else if (squareCount == 1)
		{
			squares[0] = (uint32_t)((uint32_t)(colors[0]) << 16) +
				(uint32_t)((colors[1]) << 8) +
				(uint32_t)(colors[2]);

			for (int index = 0; index < 3; index++)
				colors[index] = colors[index] / 3;
		}
		else if (squareCount == 2)
		{
			squares[0] = (uint32_t)((uint32_t)(colors[0]) << 16) +
				(uint32_t)((colors[1]) << 8) +
				(uint32_t)(colors[2]);
		}
		else
		{
			squares[0] = (uint32_t)0;
		}



		for (int index = 0; index < 4; index++)
		{
			drawLine(squares[index], 3 - index, 3 - index, 4 + index, 3 - index);
			drawLine(squares[index], 3 - index, 3 - index, 3 - index, 4 + index);
			drawLine(squares[index], 3 - index, 4 + index, 4 + index, 4 + index);
			drawLine(squares[index], 4 + index, 3 - index, 4 + index, 4 + index);
		}
	}

}

void SquareItLeftDefault()
{
	static int squareCount = 0;
	static int animCount = 0;
	static int colors[3] = { 0, 0, 0 };
	int animDelay = 100;
	int squareInterval = 7;

	static uint32_t squares[8] = { (uint32_t)0, (uint32_t)0, (uint32_t)0, (uint32_t)0,
		(uint32_t)0, (uint32_t)0, (uint32_t)0, (uint32_t)0 };

	if (anim_reset)
	{
		clearScreen();
		anim_reset = false;
		for (int index = 0; index < 8; index++)
			squares[index] = (uint32_t)0;

		for (int index = 0; index < 3; index++)
			colors[index] = 0;

		animCount = 100;
	}

	animCount++;
	if (animCount > animDelay)
	{
		animCount = 0;
		squareCount++;

		for (int index = 7; index >= 0; index--)
		{
			squares[index + 1] = squares[index];
		}

		if (squareCount >= squareInterval)
		{
			colors[0] = random(125, 150);
			colors[1] = random(125, 150);
			colors[2] = 0;

			squares[0] = (uint32_t)((uint32_t)(colors[0]) << 16) +
				(uint32_t)((colors[1]) << 8) +
				(uint32_t)(colors[2]);

			for (int index = 0; index < 3; index++)
				colors[index] = colors[index] / 3;
			squareCount = 0;
		}
		else if (squareCount == 1)
		{
			squares[0] = (uint32_t)((uint32_t)(colors[0]) << 16) +
				(uint32_t)((colors[1]) << 8) +
				(uint32_t)(colors[2]);

			for (int index = 0; index < 3; index++)
				colors[index] = colors[index] / 3;
		}
		else if (squareCount == 2)
		{
			squares[0] = (uint32_t)((uint32_t)(colors[0]) << 16) +
				(uint32_t)((colors[1]) << 8) +
				(uint32_t)(colors[2]);
		}
		else
		{
			squares[0] = (uint32_t)0;
		}



		for (int index = 0; index < 8; index++)
		{
			drawLine(squares[index], -1 - index, 3 - index, 0 + index, 3 - index);
			drawLine(squares[index], -1 - index, 3 - index, -1 - index, 4 + index);
			drawLine(squares[index], -1 - index, 4 + index, 0 + index, 4 + index);
			drawLine(squares[index], 0 + index, 3 - index, 0 + index, 4 + index);
		}
	}

}

void SquareItRightDefault()
{
	static int squareCount = 0;
	static int animCount = 0;
	static int colors[3] = { 0, 0, 0 };
	int animDelay = 100;
	int squareInterval = 7;

	static uint32_t squares[8] = { (uint32_t)0, (uint32_t)0, (uint32_t)0, (uint32_t)0,
		(uint32_t)0, (uint32_t)0, (uint32_t)0, (uint32_t)0 };

	if (anim_reset)
	{
		clearScreen();
		anim_reset = false;
		for (int index = 0; index < 8; index++)
			squares[index] = (uint32_t)0;

		for (int index = 0; index < 3; index++)
			colors[index] = 0;

		animCount = 100;
	}

	animCount++;
	if (animCount > animDelay)
	{
		animCount = 0;
		squareCount++;

		for (int index = 7; index >= 0; index--)
		{
			squares[index + 1] = squares[index];
		}

		if (squareCount >= squareInterval)
		{
			colors[0] = random(125, 150);
			colors[1] = random(125, 150);
			colors[2] = 0;

			squares[0] = (uint32_t)((uint32_t)(colors[0]) << 16) +
				(uint32_t)((colors[1]) << 8) +
				(uint32_t)(colors[2]);

			for (int index = 0; index < 3; index++)
				colors[index] = colors[index] / 3;
			squareCount = 0;
		}
		else if (squareCount == 1)
		{
			squares[0] = (uint32_t)((uint32_t)(colors[0]) << 16) +
				(uint32_t)((colors[1]) << 8) +
				(uint32_t)(colors[2]);

			for (int index = 0; index < 3; index++)
				colors[index] = colors[index] / 3;
		}
		else if (squareCount == 2)
		{
			squares[0] = (uint32_t)((uint32_t)(colors[0]) << 16) +
				(uint32_t)((colors[1]) << 8) +
				(uint32_t)(colors[2]);
		}
		else
		{
			squares[0] = (uint32_t)0;
		}



		for (int index = 0; index < 8; index++)
		{
			drawLine(squares[index], 7 - index, 3 - index, 8 + index, 3 - index);
			drawLine(squares[index], 7 - index, 3 - index, 7 - index, 4 + index);
			drawLine(squares[index], 7 - index, 4 + index, 8 + index, 4 + index);
			drawLine(squares[index], 8 + index, 3 - index, 8 + index, 4 + index);
		}
	}

}

void SquareItBrakeDefault()
{
	static int squareCount = 0;
	static int animCount = 0;
	static int colors[3] = { 0, 0, 0 };
	int animDelay = 50;
	int squareInterval = 7;

	static uint32_t squares[4] = { (uint32_t)0, (uint32_t)0, (uint32_t)0, (uint32_t)0 };

	if (anim_reset)
	{
		clearScreen();
		anim_reset = false;
		for (int index = 0; index < 4; index++)
			squares[index] = (uint32_t)0;

		for (int index = 0; index < 3; index++)
			colors[index] = 0;

		animCount = 100;
	}

	animCount++;
	if (animCount > animDelay)
	{
		animCount = 0;
		squareCount++;

		for (int index = 3; index >= 0; index--)
		{
			squares[index + 1] = squares[index];
		}

		if (squareCount >= squareInterval)
		{
			colors[0] = random(175, 225);
			colors[1] = random(5, 15);
			colors[2] = random(5, 15);

			squares[0] = (uint32_t)((uint32_t)(colors[0]) << 16) +
				(uint32_t)((colors[1]) << 8) +
				(uint32_t)(colors[2]);

			for (int index = 0; index < 3; index++)
				colors[index] = colors[index] / 3;
			squareCount = 0;
		}
		else if (squareCount == 1)
		{
			squares[0] = (uint32_t)((uint32_t)(colors[0]) << 16) +
				(uint32_t)((colors[1]) << 8) +
				(uint32_t)(colors[2]);

			for (int index = 0; index < 3; index++)
				colors[index] = colors[index] / 3;
		}
		else if (squareCount == 2)
		{
			squares[0] = (uint32_t)((uint32_t)(colors[0]) << 16) +
				(uint32_t)((colors[1]) << 8) +
				(uint32_t)(colors[2]);
		}
		else
		{
			squares[0] = (uint32_t)0;
		}



		for (int index = 0; index < 4; index++)
		{
			drawLine(squares[index], 3 - index, 3 - index, 4 + index, 3 - index);
			drawLine(squares[index], 3 - index, 3 - index, 3 - index, 4 + index);
			drawLine(squares[index], 3 - index, 4 + index, 4 + index, 4 + index);
			drawLine(squares[index], 4 + index, 3 - index, 4 + index, 4 + index);
		}
	}
}

void drawLine(uint32_t color, int x1, int y1, int x2, int y2)
{

	int  xdif = x2 - x1;
	int  ydif = y2 - y1;

	if (abs(xdif) > abs(ydif))
	{
		if (x1 > x2)
		{
			int tx = x1;
			x1 = x2;
			x2 = tx;

			int ty = y1;
			y1 = y2;
			y2 = ty;
		}
	}
	else
	{
		if (y1 > y2)
		{
			int tx = x1;
			x1 = x2;
			x2 = tx;

			int ty = y1;
			y1 = y2;
			y2 = ty;
		}
	}

	xdif = x2 - x1;
	ydif = y2 - y1;

	int curStep = 0;
	float stepTrack = 0.0;

	int intStep = 1;
	int indexStep = 1;

	if (abs(xdif) > abs(ydif))
	{
		float myStep = (float)ydif / (float)xdif;

		if (xdif < 0)
			indexStep = -1;

		if (ydif < 0)
			intStep = -1;

		for (int index = x1; index <= indexStep*x2; index += indexStep)
		{
			Rb.setPixelXY(index, y1 + curStep, color);
			stepTrack += myStep;

			if (abs(stepTrack) >= 1)
			{
				stepTrack -= float(intStep);
				curStep += intStep;
			}

		}
	}
	else
	{
		float myStep = (float)xdif / (float)ydif;

		if (ydif < 0)
			indexStep = -1;

		if (xdif < 0)
			intStep = -1;

		for (int index = y1; index <= indexStep*y2; index += indexStep)
		{
			Rb.setPixelXY(x1 + curStep, index, color);

			stepTrack += myStep;

			if (abs(stepTrack) >= 1)
			{
				stepTrack -= float(intStep);
				curStep += intStep;
			}

		}
	}
}
