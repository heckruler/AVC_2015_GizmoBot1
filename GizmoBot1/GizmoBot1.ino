/**
 * Arduiono code for TGD Autonomous Vehicle
 *
 * Authors: TGD AVC committee
 *
 * License: CC Share/Share-alike
 */
 
#include "TGD_Movement.h" // Set pin assignments in "TGD_Movement.h"
#include "location.h"

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

void setup() {
  // put your setup code here, to run once:
  init_movement();
  
  move_forward_stop(1000);     // Move forward for one second and stop.
  delay(500);                  // Pause for half a second.
  move_reverse_stop(1000);     // Move backwards for one second and stop.
  delay(500);                  // Pause for half a second.
  wheels_left();               // Turn wheels left.
  move_forward_stop(750);      // Move forward while turning left for 0.75 seconds.
  delay(500);                  // Pause for half a second.
  move_reverse_stop(750);      // Move backwards with wheels turned left for 0.75 seconds.
  delay(500);                  // Pause for half a second.
  wheels_right();              // Turn wheels right.
  move_forward_stop(750);      // Move forward while turning right for 0.75 seconds.
  delay(500);                  // Pause for half a second.
  move_reverse_stop(750);      // Move backwards with wheels turned right for 0.75 seconds.
  wheels_center();             // Turn wheels to point straight forward.
   

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

}
