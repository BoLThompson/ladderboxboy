#include "player.h"
#include "map.h"

namespace {
  const Box landBox = { //stuff under foot
    3,0,
    6,2
  };
  const Box wallBox = { //stuff on the side
    3,16,
    6,16
  };
  const Box airStopBox = { //if a wall is found here, stop air momentum
    3,16,
    6,8
  };
  const Box spearBox = {
    0,0,
    10,2
  };
};


void Player::stepFunc() {
  (this->*stepPtr)();
  //process all spears
  for (uint8_t sIndex = 0; sIndex < SPEARMAX; sIndex++) {
    if (spear[sIndex] == nullptr) continue;
    spear[sIndex]->fly();
  }
}

void Spear::fly() {
  if (!flying) return;
  x+=3;

  if (Map::collide(x, y, spearBox)) {
    flying = false;
    x += 3;
    x = x & ~(0b111);
  }
}

void Player::drawFunc(uint16_t screenX, uint16_t screenY) {
  //draw all spears
  for (uint8_t sIndex = 0; sIndex < SPEARMAX; sIndex++) {
    if (spear[sIndex] == nullptr) continue;
      sprites.drawSelfMasked(
                              spear[sIndex]->x - screenX,
                              spear[sIndex]->y - screenY,
                              Spr_::spear,
                              0
                            );
  }
  (this->*drawPtr)(screenX, screenY);
}

void Player::idleStep() {

  //walking: determine direction
  if (
      (   ab.pressed(LEFT_BUTTON) & ab.pressed(RIGHT_BUTTON)    ) || 
      ( !(ab.pressed(LEFT_BUTTON)) && !(ab.pressed(RIGHT_BUTTON))   )
    )
    hSpeed = 0;
  else {
    if (ab.pressed(LEFT_BUTTON)) {
      hSpeed = -1;
    }
    else if (ab.pressed(RIGHT_BUTTON)) {
      hSpeed = 1;
    }
  } //actually move, if possible
  if (hSpeed != 0) {
    if (! (Map::collide(x+hSpeed, y, wallBox))) {
      x+=hSpeed;
      //if there's no ground, fall
      if (  
            ( !spearCollide(x,y,landBox) ) &&
            ( !Map::collide(x,y,landBox) )
          ) {
        stepPtr = &Player::airStep;
        airTime = 0;
      }
    }
  }

  //begin a jump
  if (ab.justPressed(A_BUTTON)) {
    stepPtr = &Player::airStep;
    airTime = -15;
  }

  //attack
  if (ab.justPressed(B_BUTTON)) {
    if (ab.pressed(UP_BUTTON)) {
      //spear throw
      throwSpear();
    }
    else {
      //sword swing
    }
  }
}

bool Player::spearCollide(uint16_t boxX, uint16_t boxY, const Box hitbox) {
  boxX -= hitbox.x;
  boxY -= hitbox.y;
  for (uint8_t sIndex = 0; sIndex < SPEARMAX; sIndex++) {
    if (Util::collideRect(
                          boxX, boxY, hitbox.width, hitbox.height,
                          spear[sIndex]->x, spear[sIndex]->y, 10, 2
                          ))
      return true;
  }
  return false;
}

void Player::throwSpear() {
  for (uint8_t sIndex = 0; sIndex < SPEARMAX; sIndex++) {
    if (spear[sIndex] == nullptr) {
      spear[sIndex] = new Spear;
      spear[sIndex]->x = x;
      spear[sIndex]->y = y-11;
      break;
    }
  }
}


void Player::airStep() {
  //handle vertical velocity and momentum
  if (airTime > 12) {
    y+=2;
  }
  else if (airTime > 5) {
    y+=1;
  }
  else if (airTime < -12) {
    y -=2;
  }
  else if (airTime < -5) {
    y -=1;
  }

  //if we have horizontal momentum,
  if (hSpeed != 0) {
    //try to move that way
    if (! (Map::collide(x+hSpeed, y, wallBox)) ) {
      x+=hSpeed;
    }
    //if there's a wall at head-height,
    else if (Map::collide(x+hSpeed, y, airStopBox)) {
      hSpeed = 0; //lose momentum
    }
  }

  //attack
  if (ab.justPressed(B_BUTTON)) {
    if (ab.pressed(UP_BUTTON)) {
      //spear throw
      throwSpear();
    }
    else {
      //sword swing
    }
  }

  //if we're moving down,
  if (airTime >= 0) {
    //look for ground
    if ( spearCollide(x,y,landBox) ) {
      stepPtr = &Player::idleStep;
    }

    if ( Map::collide(x,y,landBox) ) {
      y += 3;
      y = y & ~(0b111);
      stepPtr = &Player::idleStep;
    }
  }
  
  //airTimer count
  if (airTime < 127) 
    airTime++;
}

void Player::idleDraw(uint16_t screenX, uint16_t screenY) {
  sprites.drawSelfMasked(x-8-screenX,y-16-screenY,sprite,0);
}