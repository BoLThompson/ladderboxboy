#ifndef PLAYER_H
#define PLAYER_H

#include "global.h"
#include "entity.h"

class Spear: public Entity {
  public:
    uint16_t x;
    uint16_t y;
    bool flying = true;
    void stepFunc(){};
    void drawFunc(uint16_t screenX, uint16_t screenY){};
    
    void fly();
};

class Player: public Entity {
  private:
    int8_t hSpeed = 0;
    int8_t airTime = 0;
    const uint8_t* sprite = Spr_::swordman;

    #define SPEARMAX 4
    Spear *spear[SPEARMAX];

    void (Player::*stepPtr)() = &Player::idleStep;
    void (Player::*drawPtr)(uint16_t screenX, uint16_t screenY) = &Player::idleDraw;

    void idleStep();
    void idleDraw(uint16_t screenX, uint16_t screenY);
    void airStep();

    void throwSpear();
  public:
    uint16_t x = 24;
    uint16_t y = 56;

    bool spearCollide(uint16_t boxX, uint16_t boxY, const Box hitbox);

    void stepFunc();
    void drawFunc(uint16_t screenX, uint16_t screenY);

    Player() {
      for (uint8_t ii = 0; ii < SPEARMAX; ii++) {
        spear[ii] = nullptr;
      }
    }
    ~Player() {
      delete [] spear;
    }
};

#endif