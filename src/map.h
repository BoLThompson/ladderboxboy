#ifndef MAP_H
#define MAP_H
#include "global.h"

namespace Map {
  extern uint8_t width;
  extern uint8_t height;
  extern uint16_t cameraX;
  extern uint16_t cameraY;
  void draw(uint16_t x, uint16_t y);
  uint8_t getTileAt(uint8_t x, uint8_t y);
  void init();
  bool collide(uint16_t x, uint16_t y, const Box hitbox);
};

#endif