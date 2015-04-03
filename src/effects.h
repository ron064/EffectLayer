#pragma once
#include <pebble.h>  
  
#define WINDOW_WIDTH 144  

// inverter effext.
// fb_a: matix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_invert(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position);

// vertical mirror effext.
// fb_a: matix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_mirror_vertical(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position);


// horizontal mirror effext.
// fb_a: matix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_mirror_horizontal(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position);