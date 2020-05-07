#include <Arduino.h>
#include <Arduboy2.h>

#include "global.h"

// director d;

void setup() {

  //arduboy stuff
  ab.setFrameRate(FPS); //framerate to global def
  ab.begin();            //init that shit
  ab.clear();           //clear the screen of any dumb crap that was there before
}

void loop() {

  if (!ab.nextFrame()) return;  //wait for next frame
  ab.clear();                   //blank the screen
  ab.pollButtons();             //hur durr

  ab.display();                 //make the screen happen
}