#pragma once
#include <pebble.h>  

typedef void effect_cb(uint8_t *bitmap_data, int bytes_per_row, GRect position, void* param);

// inverter effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
effect_cb effect_invert;

// vertical mirror effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
effect_cb effect_mirror_vertical;


// horizontal mirror effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
effect_cb effect_mirror_horizontal;

// Rotate 90 degrees
// Added by Ron64
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
// right true: rotate right/clockwise false: rotate left/counter_clockwise
effect_cb effect_rotate_90_degrees;

// blur effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
// radius: blur radius
effect_cb effect_blur;