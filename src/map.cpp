#include "map.h"
#include "assets.h"

uint8_t Map::width;
uint8_t Map::height;

namespace {
  // tileset;
  const uint8_t *mapPointer;
};

void Map::init() {  //TODO: take map index as argument
  mapPointer = stage1_1;
  width = pgm_read_byte(mapPointer);
  height = pgm_read_byte(mapPointer+1);
}

uint8_t Map::getTileAt(uint8_t x, uint8_t y) {
  return pgm_read_byte(x+(y*width)+(mapPointer+2));
}

void Map::draw(uint16_t x, uint16_t y) {
  uint8_t tileIndex;
  uint16_t byteIndex = 0;

  uint8_t startX = x / 8;
  uint8_t startY = y / 8;

   for (uint8_t tileY = startY; tileY <= (startY+(SCREEN_HEIGHT/TILE_SIZE)); tileY++){ //iterate through rows
    for (uint8_t tileX = startX; tileX <= (startX+(SCREEN_WIDTH/TILE_SIZE)); tileX++) { //iterate through tiles
      //determine tile type
      tileIndex = getTileAt(tileX,tileY);

      //draw the tile
      sprites.drawOverwrite(tileX*TILE_SIZE-x, tileY*TILE_SIZE-y, tiles, tileIndex); //draw tile
    }
  }
}

bool Map::collide(uint16_t x, uint16_t y, const Box hitbox) {
  if  ((hitbox.x >= x) || (x+hitbox.width-1 > width*TILE_SIZE))  //test for off the left or off the right
    return(true); //no escaping

  // if ((y+hitbox.height)-1 || ((hitbox.y >= y) > height*TILE_SIZE)) //test for off the vertical bounds
  //   return(false); //don't care

  x-=hitbox.x;
  y-=hitbox.y;
  uint16_t tx1 = x/TILE_SIZE;
  uint16_t tx2 = (x+hitbox.width-1)/TILE_SIZE;
  uint16_t ty1 = y/TILE_SIZE;
  uint16_t ty2 = (y+hitbox.height-1)/TILE_SIZE; //note that we have to check the tiles immediately past ty2 and tx2

  for (uint16_t tileX = tx1; tileX <= tx2; tileX++) {
    for (uint16_t tileY = ty1; tileY <= ty2; tileY++) {
      if (getTileAt(tileX, tileY) == 0) { //test for solid
        if (Util::collideRect(tileX*TILE_SIZE, tileY*TILE_SIZE, TILE_SIZE, TILE_SIZE, x, y, hitbox.width, hitbox.height)) {
          return true;
        }
      }
    }
  }

  return (false);
}