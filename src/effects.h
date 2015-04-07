#pragma once
#include <pebble.h>  

//pebble screen width in bytes (essentially bytes per row)  
#ifdef PBL_COLOR    
  #define WINDOW_WIDTH 144  
#else  
  #define WINDOW_WIDTH 20
#endif

// inverter effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_invert(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position);

// vertical mirror effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_mirror_vertical(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position);


// horizontal mirror effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_mirror_horizontal(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position);

// Rotate 90 degrees
// Added by Ron64
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
// right true: rotate right/clockwise false: rotate left/counter_clockwise
void effect_rotate_90_degrees(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position, bool right);

// blur effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
// radius: blur radius
void effect_blur(uint8_t (*fb_a)[WINDOW_WIDTH], GRect position, uint8_t radius);