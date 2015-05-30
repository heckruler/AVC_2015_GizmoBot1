/**
 * Arduiono code for TGD Autonomous Vehicle
 *
 * Authors: TGD AVC committee
 *
 * License: CC Share/Share-alike
 */
 
#include "TGD_Movement.h" // Set pin assignments in "TGD_Movement.h"
#include "location.h"

#include <SimpleTimer.h> //Or whatever, I just grabbed the first one I found. Hopefully it doesn't interfere with whatever timer the GPS is using

/** init_gps() */
void init_gps() {
  Serial.print(F("init_gps() ... "));
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_5HZ);
  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  // start interrupt timer
  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
  
  Serial.println(F("OK!"));
}


void isr1ms()
{
  gTimer++; //Increment timer for move_events
}

void setup() {
  // put your setup code here, to run once:
  move_init();
  timer.setInterval(1, isr1ms);  //I've no idea if a 1ms isr will choke an arduino
 
  move_forwardStop(1000);     // Move forward for one second and stop.
  delay(1500);                // Pause for one and a half seconds to let that happen.
  move_reverseStop(1000);     // Move backwards for one second and stop.
  delay(1500);                // Pause to let that happen. I could look at sensors here. 
  move_wheelsLeft();          // Turn wheels left.
  move_forwardStop(750);      // Move forward while turning left for 0.75 seconds.
  delay(1500);                // Pause to let that happen. 
  move_reverseStop(750);      // Move backwards with wheels turned left for 0.75 seconds.
  delay(1500);                // Pause to let that happen.
  wheels_right();             // Turn wheels right.
  move_forwardStop(750);      // Move forward while turning right for 0.75 seconds.
  delay(1500);                // Pause to let that happen.
  move_reverseStop(750);      // Move backwards with wheels turned right for 0.75 seconds.
  move_wheelsCenter();        // Turn wheels to point straight forward.
   

}

void loop() {
  // put your main code here, to run repeatedly:
  
  // check current and destination location.
  // calculate heading to get from a to b.
  // compare it to current heading.
  // check for obstacles.
  // turn vehicle to correct heading.
  // check for obstacles.
  // move forward for 1 second and stop.

  timer.run();  
}
