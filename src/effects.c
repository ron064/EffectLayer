#include <pebble.h>
#include "effects.h"

// inverter effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer  
void effect_invert(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position) {
  
  for (int y = 0; y < position.size.h; y++)
     for (int x = 0; x < position.size.w; x++)
        fb_a[y + position.origin.y][x + position.origin.x] = ~fb_a[y + position.origin.y][x + position.origin.x];
  
}

// vertical mirror effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_mirror_vertical(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position) {
  uint8_t temp_pixel;  

  for (int y = 0; y < position.size.h / 2 ; y++)
     for (int x = 0; x < position.size.w; x++){
        temp_pixel = fb_a[y + position.origin.y][x + position.origin.x];
        fb_a[y + position.origin.y][x + position.origin.x] = fb_a[position.origin.y + position.size.h - y - 2][x + position.origin.x];
        fb_a[position.origin.y + position.size.h - y - 2][x + position.origin.x] = temp_pixel;
     }
}


// horizontal mirror effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_mirror_horizontal(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position) {
  uint8_t temp_pixel;  

  for (int y = 0; y < position.size.h; y++)
     for (int x = 0; x < position.size.w / 2; x++){
        temp_pixel = fb_a[y + position.origin.y][x + position.origin.x];
        fb_a[y + position.origin.y][x + position.origin.x] = fb_a[y + position.origin.y][position.origin.x + position.size.w - x - 2];
        fb_a[y + position.origin.y][position.origin.x + position.size.w - x - 2] = temp_pixel;
     }
}

// Rotate 90 degrees
// Added by Ron64
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
// right true: rotate right/clockwise false: rotate left/counter_clockwise
void effect_rotate_90_degrees(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position, bool right){
  uint8_t qtr, xCn, yCn, temp_pixel;
  xCn= position.origin.x + position.size.w /2;
  yCn= position.origin.y + position.size.h /2;
  qtr=position.size.w;
  if (position.size.h < qtr)
    qtr= position.size.h;
  qtr= qtr/2;

  for (int c1 = 0; c1 < qtr; c1++)
    for (int c2 = 1; c2 < qtr; c2++){
      temp_pixel = fb_a[yCn +c1][xCn +c2];
      if (right){
        fb_a[yCn +c1][xCn +c2] = fb_a[yCn -c2][xCn +c1];
        fb_a[yCn -c2][xCn +c1] = fb_a[yCn -c1][xCn -c2];
        fb_a[yCn -c1][xCn -c2] = fb_a[yCn +c2][xCn -c1];
        fb_a[yCn +c2][xCn -c1] = temp_pixel;
      }
      else{
        fb_a[yCn +c1][xCn +c2] = fb_a[yCn +c2][xCn -c1];
        fb_a[yCn +c2][xCn -c1] = fb_a[yCn -c1][xCn -c2];
        fb_a[yCn -c1][xCn -c2] = fb_a[yCn -c2][xCn +c1];
        fb_a[yCn -c2][xCn +c1] = temp_pixel;
      }
     }
}