#pragma once
#include <pebble.h>  


// inverter effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_invert(uint8_t *bitmap_data, int bytes_per_row, GRect position);

// vertical mirror effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_mirror_vertical(uint8_t *bitmap_data, int bytes_per_row, GRect position);


// horizontal mirror effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_mirror_horizontal(uint8_t *bitmap_data, int bytes_per_row, GRect position);

// Rotate 90 degrees
// Added by Ron64
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
// right true: rotate right/clockwise false: rotate left/counter_clockwise
void effect_rotate_90_degrees(uint8_t *bitmap_data, int bytes_per_row, GRect position, bool right);

// blur effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
// radius: blur radius
void effect_blur(uint8_t *bitmap_data, int bytes_per_row, GRect position, uint8_t radius);