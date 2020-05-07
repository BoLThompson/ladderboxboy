from PIL import Image
import json
import os

progHeader = "PROGMEM const uint8_t "
progTail = "[] = {"

f = open("src\\assets.h","w+")

f.write("#ifndef ASSET_H\r#define ASSET_H\r\r")

f.write("//  Begin tileset dump...\r")
tileSize = 8

for filename in os.listdir("assets\\tilesets"): #each image in the tileset folder

  f.write("//  "+filename+"\r")                             #filename comment
  f.write(progHeader+filename[:-4]+progTail)  #variable declaration
  #(variable name is filename minus the extension)
  f.write("\r  "+str(tileSize)+","+str(tileSize)+",\r")

  image = Image.open("assets\\tilesets\\"+filename, "r") #open the bmp image file
  pix_val = list(image.getdata())                   #list of pixels (zero or 255)

  # for v in pix_val:
  #   print v


  x = 0
  startX = 0
  # read each column of tiles
  while (startX < image.width):
    startY = 0
    while (startY < image.height):
      f.write("  ")
      #########################################################
      x = startX
      # this does a single tile
      while (x < (startX+tileSize)) :
        # read a column of pixels
        y = startY+tileSize
        currchar = 0
        while (y > (startY)) :
          y = y-1
          currchar = currchar << 1
          if ( pix_val[(y*image.width)+x][0] != 0 ):
            currchar = currchar|1
        f.write(str(hex(currchar))+",")
        x = x+1
      #######################################################
      startY = startY+tileSize
      f.write("\r")
    startX = x

  f.write("};\r\r")


f.write("//  Begin tileset dump...\r")
for filename in os.listdir("assets\\maps"): #each map in the maps folder
  mapFile = open("assets\\maps\\"+filename, "r")
  map = json.load(mapFile)
  f.write("//  "+filename+"\r")
  f.write(progHeader+filename[:-5]+progTail)
  f.write("\r  "+str(map["width"])+","+str(map["height"])+",")
  dataIndex = 0
  tileY = 0
  while (tileY < map["height"]):
    f.write("\r  ")
    tileX = 0
    while (tileX < map["width"]):
      f.write(str(hex(map["data"][dataIndex]))+",")
      dataIndex = dataIndex+1
      tileX = tileX+1
    tileY = tileY+1
  f.write("\r};\r\r")

f.write("//  Begin sprite dump...\r")
SPRITE_HEIGHT = 16
for filename in os.listdir("assets\\sprites"):

  image = Image.open("assets\\sprites\\"+filename, "r") #open the bmp image file

  f.write("//  "+filename+"\r")                             #filename comment
  f.write(progHeader+filename[:-4]+progTail)  #variable declaration
  #(variable name is filename minus the extension)

  # get image width
  # assume image height of 24 pixels
  f.write("\r  "+str(image.width)+","+str(SPRITE_HEIGHT)+",\r")

  pix_val = list(image.getdata())                   #list of pixels (zero or 255)


  # write a byte of vertical pixels
  # write the next byte over

  x = 0
  startX = 0
  # read each column of tiles
  while (startX < image.width):
    startY = 0
    while (startY < image.height):
      f.write("  ")
      #########################################################
      x = startX
      # this does a single tile
      while (x < (startX+image.width)) :
        # read a column of pixels
        y = startY+8
        currchar = 0
        while (y > (startY)) :
          y = y-1
          currchar = currchar << 1
          if ( pix_val[(y*image.width)+x][0] > 128 ):
            currchar = currchar|1
        f.write(str(hex(currchar))+",")
        x = x+1
      #######################################################
      startY = startY+8
      f.write("\r")
    startX = x
  f.write("};\r\r")


  
f.write("#endif")
f.close()