#include "global.h"

Arduboy2Base ab;
Sprites sprites;

//FIXME: the y values are truncated to uint8_t. this could be dangerous?
bool Util::collideRect(int16_t x1, int8_t y1, uint8_t width1, uint8_t height1, int16_t x2, int8_t y2, uint8_t width2, uint8_t height2){
  return !(x1            >= x2 + width2  ||
           x1 + width1   <= x2           ||
           y1            >= y2 + height2 ||
           y1 + height1  <= y2);
}