#ifndef __TGD_MOVEMENT_H_
#define __TGD_MOVEMENT_H_

// 5/26/15 moving implementation to .c, replacing halting code with event shindig

// gTimer needs to be incremented in the main body of code each ms. 
// In the arduino's main loop, call move_Events()

extern int gTimer;


//HW def
#define forwardPin 7
#define backPin    6
#define leftPin    5
#define rightPin   4
//Out of curiosity what does the car do when told to go forwards AND backwards at the same time?

//millisec of counter-thrust to halt movement. ie, stop coasting.
#define HALT_PULSE_DURATION 50

#define HALT_OFF     0 
#define HALT_FORWARD 1 
#define HALT_REVERSE 2


// Initialize movement library - eliminate floating voltages and set pins to output
void move_init();

// Handles timed events
void move_events();

//You could also have... you know... just_move_forward().  No stop time. Depend on the sensors/gps to tell you when to stop.  Whatever floats your autonomous boat.

// Move forward and coast
void move_forward(int ms_time);

// Move forward and stop
void move_forwardStop(int ms_time);

// Move in reverse and coast
void move_reverse(int ms_time);

// Move in reverse and stop
void move_reverseStop(int ms_time);

// Turn wheels left
void move_wheelsLeft();

// Turn wheels right
void move_wheelsRight();

// Center wheels
void move_wheelsCenter();

#endif __TGD_MOVEMENT_H_
