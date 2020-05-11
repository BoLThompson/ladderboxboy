#ifndef ENTITY_H
#define ENTITY_H

#include "global.h"

class Entity {
  private:
  public:
    virtual void stepFunc();
    virtual void drawFunc(uint16_t screenX, uint16_t screenY);
};

#endif