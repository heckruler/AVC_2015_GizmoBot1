//Philip Haubrich
// I recommend alternatives to this business with setting pin states.
// At first blush, I'd just try a voltage divider. 
// 5V output from pin -> 10K ohm res --V--> 20K ohm res -> GND
//                                     \-> 3.3V to controlls.
// You just shift the voltage down.
// http://www.savagecircuits.com/content.php?85-Mixed-Voltage-Systems-Interfacing-5V-and-3-3V-Devices
//
// Or you could look at something like a logic level converter 
//   https://www.sparkfun.com/products/12009

#include "TGD_Movement.h"
//#include "arduinoPinIO.h"  //For HIGH/LOW  INPUT/OUT pinMode, digitalWrite   ...I think this is just defaulted into the arduino compiler... 

int gTimer=0;

//You COULD have a generic system of events. But there's really just to two:
// 1) stop in X seconds
// 2) Reverse direction in X seconds, stop in another 50ms.  
// They don't even need to overlap. So while generic is nice, hardcode simple shit.
//int gEvents[3];
//  with generic events you could queue up actions like: TurnLeft(5msInTheFuture, DoSoFor20ms) But meh, keep it simple
int gStopTime= MAX_INT;
int gHaltFlag=0;






//You really just want to use digtalWrite(pin, HIGH);  
//Axe this and :%s:digital3vWrite:digitalWrite
static void digital3vWrite(int pin, int state)
{
  state==HIGH? state=INPUT : state=OUPUT; 
  pinMode(pin, state); 
}


// Initialize movement library - eliminate floating voltages and set pins to output
void move_init() 
{
  pinMode(forwardPin, OUTPUT);
  pinMode(backPin, OUTPUT);
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);

  digitalWrite(forwardPin, LOW);
  digitalWrite(backPin, LOW);
  digitalWrite(leftPin, LOW);
  digitalWrite(rightPin, LOW);
}

// Handles timed events
void move_events()
{
  if(gStopTime < gTimer)
  {
    return;  
  }
  //Else, there is an outstanding event that needs to happen

  
  //Dealing with those "and stop" functions.  "Halting". 
  //A 1 time short thrust in the opposite direction
  if(gHaltFlag)
  {
    if(gHaltFlag == HALT_FORWARD)
    {
      digital3vWrite(forwardPin, LOW);
      digital3vWrite(backPin, HIGH);
    } 
    else// HALT_REVERSE
    {
      digital3vWrite(backPin, LOW);
      digital3vWrite(forwardPin, HIGH);
    }
    gStopTime = gTimer + HALT_PULSE_DURATION;
    gHaltFlag = HALT_OFF;
  }
  else //Handled regular timed movement and the 2nd action of halt-thrusts
  {
    //STOP
    digital3vWrite(forwardPin, LOW);
    digital3vWrite(backPin, LOW);
  }
}


// Move forward and coast
void move_forward(ms_time) 
{
  digital3vWrite(forwardPin, HIGH);
  gStopTime = gTimer + ms_time;
  gHaltFlag = HALT_OFF;
}

// Move forward and stop
void move_forwardStop(ms_time) 
{
  digital3vWrite(forwardPin, HIGH);
  gStopTime = gTimer + ms_time;
  gHaltFlag = HALT_FORWARD;
}

// Move in reverse and coast
void move_reverse(ms_time) 
{
  digital3vWrite(backPin, HIGH);
  gStopTime = gTimer + ms_time;
  gHaltFlag = HALT_OFF;
}

// Move in reverse and stop
void move_reverseStop(ms_time) 
{
  digital3vWrite(backPin, HIGH);
  gStopTime = gTimer + ms_time;
  gHaltFlag = HALT_REVERSE;
}

// Turn wheels left
void move_wheelsLeft()
{
  digital3vWrite(rightPin, LOW);
  digital3vWrite(leftPin, HIGH);
}

// Turn wheels right
void move_wheelsRight()
{
  digital3vWrite(leftPin, LOW);
  digital3vWrite(rightPin, HIGH);
}

// Center wheels
void move_wheelsCenter()
{
  digital3vWrite(rightPin, LOW);
  digital3vWrite(leftPin, LOW);
}


