
#define flexConstant 500
#define blinkMax 250
#define black 0
#define green 1
#define blue 2
#define teal 3
#define red 4
#define yellow 5
#define purple 6
#define white 7


const int pin_row_power = 9;
const int pin_row_clock = 7;
const int pin_row_data = 8;
const int pin_col_clock = 5;
const int pin_col_data = 6;
const int pin_left_light = 3;
const int pin_right_light = 4;


const int leftButton = 11;
const int rightButton = 12;
const int animSense = 0; 
const int brakeSense = 1;

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



// 0
boolean canvas[192] = {
  // green                                          // blue                                          // red
//0,   1      2     3     4      5     6     7      8     9    10    11    12    13    14    15     16    17     18    19    20    21    22     23
  LOW , LOW , LOW , LOW , LOW , LOW , LOW , LOW ,  HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, HIGH , HIGH, HIGH, HIGH, HIGH, HIGH , HIGH,   // 0
  LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, LOW , LOW , LOW , LOW , LOW , LOW , LOW ,  HIGH, HIGH , HIGH, HIGH, HIGH, HIGH, HIGH , HIGH,   // 1
  LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, HIGH , LOW , LOW , LOW , LOW , LOW  , LOW ,   // 2
  LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, HIGH , LOW , HIGH, LOW , HIGH, HIGH , HIGH,   // 3
  LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, HIGH , LOW , HIGH, LOW , HIGH, HIGH , HIGH,   // 4
  LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, HIGH , LOW , HIGH, LOW , HIGH, HIGH , HIGH,   // 5
  LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, HIGH , LOW , HIGH, LOW , HIGH, HIGH , HIGH,   // 6
  LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, LOW , HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,  HIGH, HIGH , LOW , HIGH, LOW , HIGH, HIGH , HIGH,   // 7
};


int timerTracker = 0;
int timeDelay = 100;

int blink_delay = 0;
boolean blink_state = LOW;





void setup()
{

  //Serial.begin(9600);
  
  // setting pins
  pinMode(pin_row_power, OUTPUT);
  pinMode(pin_row_clock, OUTPUT);
  pinMode(pin_row_data, OUTPUT);
  pinMode(pin_col_clock, OUTPUT);
  pinMode(pin_col_data, OUTPUT);
  pinMode(pin_left_light, OUTPUT);
  pinMode(pin_right_light, OUTPUT);
  
  digitalWrite(pin_row_power, HIGH);
  digitalWrite(pin_row_clock, LOW);
  digitalWrite(pin_row_data, LOW);
  digitalWrite(pin_col_clock, LOW);
  digitalWrite(pin_col_data, LOW);
  digitalWrite(pin_left_light, LOW);
  digitalWrite(pin_right_light, LOW);
  

  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  
  leftOn = false;
  rightOn = false;
  leftDown = true;
  rightDown = true;
  breakDown = true;
  breakOn = false;
  
  
 _line = 0;
 
 anim_reset = true;
 anim_old = 0;
 
 
  //Serial.begin(9600);
}





void loop()
{

    int leftState, rightState;

    //////////////////////////////////////////////////////////
    // Read Inputs
    int brakeValue = analogRead(brakeSense);
    int animValue = analogRead(animSense)/500;
    leftState = digitalRead(leftButton);
    rightState = digitalRead(rightButton);
  
  
    //////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////
    // Logic for inputs
    
    if(leftState == HIGH && !leftDown && !leftOn)
    {
      leftOn = true;
      leftDown = true;
      delayCounter = 0;
      clearScreen();
      anim_reset = true;

      rightDown = false;
      rightOn = false;
    }
    
    if(leftState == HIGH && !leftDown && leftOn)
    {
      leftOn = false;
      leftDown = true;
      delayCounter = 0;
    }
  
    
    if(leftState == LOW && leftDown)
    {
      leftDown = false;
      anim_reset = true;
    }
    
    if(rightState == HIGH && !rightDown && !rightOn)
    {
      rightOn = true;
      rightDown = true;
      delayCounter = 0;
      clearScreen();
      anim_reset = true;
      
      leftDown = false;
      leftOn = false;
   }
    
    if(rightState == HIGH && !rightDown && rightOn)
    {
      rightOn = false;
      rightDown = true;
      delayCounter = 0;

    }
  
    
    if(rightState == LOW && rightDown)
    {
      rightDown = false;
            anim_reset = true;
    }
    
    
    
    
    
     if(flexConstant >= brakeValue && breakOn == false)
     {
       breakOn = true;
      breakDown = true;
      delayCounter = 0;
      clearScreen();
      anim_reset = true;
    }
    else if(flexConstant < brakeValue && breakOn == true)
    {
      breakOn = false;
      breakDown = false;
      delayCounter = 0;
      breakDown = false;
      clearScreen();
      anim_reset = true;
    }
    
    //////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////
    // increment the row
    if(_line < 8)
      {
        pushByte(LOW, pin_row_data, pin_row_clock);
         _line++;
      }
     else
     {
        pushByte(HIGH, pin_row_data, pin_row_clock); 
        _line=0;
      }
    ///////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////
    // create new track line
    int place = (_line)*24;
    pushBytes(canvas, place, 24, pin_col_data, pin_col_clock);
    ///////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////
    // Raise up power to turn off leds
    digitalWrite(pin_row_power, HIGH);
    ///////////////////////////////////////////////////////////
    
    
  /*
  Serial.print("anim_old: ");
  Serial.print(anim_old);
  Serial.print("  Value: ");
  Serial.println(animValue);
  
  //delay(100);
  */
  
    ///////////////////////////////////////////////////////////
    // Animation Code
    if(!leftOn && !rightOn && !breakOn)
    {
      if(anim_old != animValue){
        anim_reset = true;
        clearScreen();
      }
      
      if(animValue == 0)
        sillyAnimation();
      else
        americanFlag();
        
      anim_old = animValue;  
    }
    else if(breakOn)
    {
      break_Signal();
    }
    else if(leftOn && !rightOn && !breakOn)
    {
      left_Signal();
    }
    else if(!leftOn && rightOn && !breakOn)
    {
      right_Signal();
    }
    
    // End Animation
    ////////////////////////////////////////////////////////      


    //////////////////////////////////////////////////////////
    // raise for lights
    digitalWrite(pin_row_power, LOW);
    //////////////////////////////////////////////////////////
    
    
    /////////////////////////////////////////////////////////
    // Left Right Signal
    
    blink_delay = blink_delay + 1;
    
    if(blink_delay >= blinkMax)
    {
     
      blink_state = !blink_state;
       if(leftOn && !rightOn && !breakOn)
         digitalWrite(pin_left_light, blink_state);
       else
         digitalWrite(pin_left_light, LOW);
  
       if(!leftOn && rightOn && !breakOn)
         digitalWrite(pin_right_light, blink_state);
       else
         digitalWrite(pin_right_light, LOW);
       
      blink_delay = 0;
    }

    
    
    // End Signal
    /////////////////////////////////////////////////////////
    
    
    
    timerTracker++;

}

void clearScreen()
{
    ///////////////////////////////////////////////////////////
    // Clear screen
    for(int index = 0; index < 192; index++)
    {
       canvas[index] = HIGH;
    }
    ///////////////////////////////////////////////////////////
}

void left_Signal()
{
  
  static int place = 0;
  static int color_ = 5;
  
  if(anim_reset)
  {
    place = 0;
    color_ = 5;
    anim_reset = false;
  }
  
  if(timerTracker > timeDelay)
      {
        timerTracker = 0;
        drawLine(color_,3-place,3-place,3-place,4+place);
        drawLine(color_,4+place,4+place,3-place,4+place);
        place++;
        
        if(place > 3)
        {
          place = 0;
          if(color_ == 5)color_ = 0;
          else color_ = 5;
        }
      }
      
      delay(1);
}

void right_Signal()
{
  static int place = 0;
  static int color_ = 5;
  
    if(anim_reset)
  {
    place = 0;
    color_ = 5;
    anim_reset = false;
  }


  if(timerTracker > timeDelay)
      {
        timerTracker = 0;
        drawLine(color_,3-place,3-place,4+place,3-place);
        drawLine(color_,4+place,4+place,4+place,3-place);
        place++;
        
        if(place > 3)
        {
          place = 0;
          if(color_ == 5)color_ = 0;
          else color_ = 5;
        }
      }
      delay(1);
}

void break_Signal()
{
  static int timedelay = 0;
  static int color_ = red;
  
    if(anim_reset)
  {
    timedelay = 0;
    color_ = red;
    anim_reset = false;
  }

  timedelay++;
  drawSquare(color_, 0, 0, 7,7, true);

  if(timedelay > 100)
  {
    if(color_ == red)
      color_ = yellow;
    else
      color_ = red;
    
    timedelay = 0;
  }

      delay(1);
}



void americanFlag()
{
  
  static int timedelay = 0;
  static int rowstep = 0;
  
    if(anim_reset)
  {
    timedelay = 0;
    rowstep = 0;
    
    drawLine(blue, 7, 7, 4, 4);
    drawLine(blue, 7, 6, 5, 4);
    drawLine(blue, 7, 1, 5, 3);
    drawLine(blue, 7, 5, 6, 4);
    drawLine(blue, 7, 2, 6, 3);
    drawLine(blue, 7, 4, 7, 3);
    drawLine(white, 6, 7, 6, 7); 
    drawLine(white, 5, 7, 5, 7); 
    drawLine(red,   5, 6, 4, 7); 
    drawLine(red,   4, 6, 3, 7); 
    drawLine(white, 4, 5, 2, 7); 
    drawLine(white, 3, 5, 1, 7); 
    drawLine(red,   7, 0, 0, 7); 
    drawLine(red,   6, 0, 0, 6); 
    drawLine(white, 5, 0, 0, 5); 
    drawLine(white, 4, 0, 0, 4); 
    drawLine(red,   3, 0, 0, 3); 
    drawLine(red,   2, 0, 0, 2); 
    drawLine(white, 1, 0, 0, 1); 
    drawLine(white, 0, 0, 0, 0); 
    anim_reset = false;

  }
  
  if(timedelay > 1000)
  {
    int color1 = white;
    int color2 = red;
    
    if(rowstep == 0)
    {
      color1 = red;
      color2 = white;  
      rowstep = 1;
    }
    else
    {
      rowstep = 0;
    }

    
    drawLine(color1, 6, 7, 6, 7); 
    drawLine(color1, 5, 7, 5, 7); 
    drawLine(color2, 5, 6, 4, 7); 
    drawLine(color2, 4, 6, 3, 7); 
    drawLine(color1, 4, 5, 2, 7); 
    drawLine(color1, 3, 5, 1, 7); 
    drawLine(color2, 7, 0, 0, 7); 
    drawLine(color2, 6, 0, 0, 6); 
    drawLine(color1, 5, 0, 0, 5); 
    drawLine(color1, 4, 0, 0, 4); 
    drawLine(color2, 3, 0, 0, 3); 
    drawLine(color2, 2, 0, 0, 2); 
    drawLine(color1, 1, 0, 0, 1); 
    drawLine(color1, 0, 0, 0, 0); 
 
    timedelay = 0;
  }
  
  timedelay++;
  
  delay(1);
  
}

void matrix()
{
  static int timedelay = 0;
  static int rowstep = 0;
  
    if(anim_reset)
  {
    clearScreen();
    timedelay = 0;
    rowstep = 0;
    
    anim_reset = false;

  }
  
  if(timedelay > 1000)
  {
 
    timedelay = 0;
  }
  
  timedelay++;
  
  delay(1);
}



void sillyAnimation()
{
  
  static int x[4] = {1, 1, 6, 6};
  static int y[4] = {1, 6, 6, 1};

  if(timerTracker > timeDelay)
      {
        timerTracker = 0;
        
        for(int index = 0; index < 4; index++)
        {
          if(x[index] == 1 && y[index] < 6)
            y[index]++;
          else if(x[index] == 6 && y[index] > 1)
            y[index]--;
          else if(y[index] == 1 && x[index] > 1)
            x[index]--;
          else if(y[index] == 6 && x[index] < 6)
            x[index]++;
        }
        
        
      }
  
  
        drawSquare(5, 0,0,7,7,false);
        drawLine(4,x[0],y[0],x[1],y[1]);
        drawLine(1,x[1],y[1],x[2],y[2]);
        drawLine(2,x[2],y[2],x[3],y[3]);
        drawLine(7,x[3],y[3],x[0],y[0]);
        
        if(timerTracker < timeDelay/2){
          drawDot(3,3,3);
          drawDot(3,4,4);
        }
        else{
          drawDot(3,3,4);
          drawDot(3,4,3);
        }
}






void drawDot(int color, int x, int y)
{
  int g = x + (24 * y);
  int b = x + 8 + (24 * y);
  int r = x + 16 + (24 * y);
  
  if(r > 191) return;
  
  switch(color)
  {
    case 0:
      canvas[g] = HIGH;
      canvas[b] = HIGH;
      canvas[r] = HIGH;
    break;
    case 1:
      canvas[g] = LOW;
      canvas[b] = HIGH;
      canvas[r] = HIGH;
    break;
    case 2:
      canvas[g] = HIGH;
      canvas[b] = LOW;
      canvas[r] = HIGH;
    break;
    case 3:
     canvas[g] = LOW;
      canvas[b] = LOW;
      canvas[r] = HIGH;
    break;
    case 4:
      canvas[g] = HIGH;
      canvas[b] = HIGH;
      canvas[r] = LOW;
    break;
    case 5:
     canvas[g] = LOW;
      canvas[b] = HIGH;
      canvas[r] = LOW;
    break;
    case 6:
      canvas[g] = HIGH;
      canvas[b] = LOW;
      canvas[r] = LOW;
    break;
    case 7:
      canvas[g] = LOW;
      canvas[b] = LOW;
      canvas[r] = LOW;
    break;
  }
}

void drawLine(int color, int x1, int y1, int x2, int y2)
{

  int  xdif = x2 - x1;
  int  ydif = y2 - y1;
  
  if(abs(xdif) > abs(ydif))
  {
    if(x1 > x2)
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
    if(y1 > y2)
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
  
  if(abs(xdif) > abs(ydif))
  {
    float myStep = (float)ydif/(float)xdif;
    
    if(xdif < 0)
      indexStep = -1;
    
    if(ydif < 0)
      intStep = -1;
    
    for(int index = x1; index <= indexStep*x2; index+=indexStep)
    {
      drawDot(color, index, y1 + curStep);
      
      stepTrack += myStep;
      
      if(abs(stepTrack) >= 1)
      {
        stepTrack -= float(intStep);
        curStep += intStep;
      }
      
    }
  }
  else
  {
    float myStep = (float)xdif/(float)ydif;
    
    if(ydif < 0)
      indexStep = -1;

    if(xdif < 0)
      intStep = -1;
    
    for(int index = y1; index <= indexStep*y2; index+=indexStep)
    {
      drawDot(color, x1 + curStep, index);
      
      stepTrack += myStep;
      
      if(abs(stepTrack) >= 1)
      {
        stepTrack -= float(intStep);
        curStep += intStep;
      }
      
    }
  }
}

void drawSquare(int color, int x1, int y1, int x2, int y2, boolean fill)
{
  int xstart = 0;
  int ystart = 0;
  
  int xend = 0;
  int yend = 0;

  if(x1 < x2){
  xstart = x1;
  xend = x2;
  }
  else{
  xstart = x2;
  xend = x1;
  }
  
  if(y1 < y2)
  {
    ystart = y1;
    yend = y2;
  }
  else
  {
    ystart = y2;
    yend = y1;
  }
  
  for(int x = xstart; x <= xend; x++)
    for(int y = ystart; y <= yend; y++)
    {
      if(fill)
        drawDot(color, x, y);
        else
        {
          if((x == xstart || x == xend)||(y == ystart || y == yend))
          {
            drawDot(color, x,y);
          }
        } 
        
    }
}


// green = [x,y] where n = x + 0 + 24 * y
// blue = [x,y] where n = x + 8 + 24 * y
// red = [x,y] where n = x + 16 + 24 * y

// 1 1 1

// 0 = black
// 1 = green
// 2 = blue
// 3 = teal
// 4 = red
// 5 = yellow
// 6 = purple
// 7 = white




// draw it to leds
void pushBytes(const boolean value[], int start, int length, int _data, int _clock)
{
  
  int _end = start + length;
  
  for(int x = start; x < _end; x++)
  {
    digitalWrite(_data, value[x]);
    digitalWrite(_clock, HIGH);
    digitalWrite(_clock, LOW);
  }
}

void pushByte(int value, int _data, int _clock)
{
    digitalWrite(_data, value);
    digitalWrite(_clock, HIGH);
    digitalWrite(_clock, LOW);
}
