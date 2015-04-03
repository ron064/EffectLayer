#include <pebble.h>
#include "effects.h"

// inverter effext.
// fb_a: matix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer  
void effect_invert(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position) {
  
  for (int y = 0; y < position.size.h; y++)
     for (int x = 0; x < position.size.w; x++)
        fb_a[y + position.origin.y][x + position.origin.x] = ~fb_a[y + position.origin.y][x + position.origin.x];
  
}

// vertical mirror effext.
// fb_a: matix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
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


// horizontal mirror effext.
// fb_a: matix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
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