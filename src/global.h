#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduboy2.h>

#include <assets.h>

#define FPS 60

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define TILE_SIZE 8
#define FIRE_BUTTON B_BUTTON
#define JUMP_BUTTON A_BUTTON

extern Arduboy2Base ab;
extern Sprites sprites;

namespace Util
{
  bool collideRect(int16_t x1, int8_t y1, uint8_t width1, uint8_t height1, int16_t x2, int8_t y2, uint8_t width2, uint8_t height2);
}

struct Box {
  uint8_t x;
  uint8_t y;
  uint8_t width;
  uint8_t height;
};

#endif