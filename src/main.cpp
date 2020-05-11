#include <Arduino.h>
#include <Arduboy2.h>

#include "global.h"


#include "player.h"
#include "map.h"

Player p;
uint16_t screenX, screenY;

void setup() {

  //arduboy stuff
  ab.setFrameRate(FPS); //framerate to global def
  ab.boot();            //init that shit
  ab.clear();           //clear the screen of any dumb crap that was there before

  Map::init();
}

void loop() {
  if (!ab.nextFrame()) return;  //wait for next frame
  ab.clear();                   //blank the screen
  ab.pollButtons();             //hur durr

  p.stepFunc();

  #define CAM_BOUND_LEFT  20
  #define CAM_BOUND_RIGHT 100

  //if the player has moved into the right camera boundary, move the camera right to correct
  if (p.x > (screenX+128)-CAM_BOUND_RIGHT) {
    screenX = p.x + CAM_BOUND_RIGHT-128;
  }
  if (p.x < screenX + CAM_BOUND_LEFT) {
    if ((int32_t) p.x - CAM_BOUND_LEFT >= 0)
      screenX = p.x - CAM_BOUND_LEFT;
    else
      screenX = 0;
  }

  Map::draw(screenX,screenY);

  p.drawFunc(screenX,screenY);

  ab.display();                 //make the screen happen
}