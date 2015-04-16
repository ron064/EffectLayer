#pragma once
#include <pebble.h>  
  
// structure of mask for masking effects
typedef struct {
  GBitmap*  bitmap_mask; // bitmap used for mask (when masking by bitmap)
  GBitmap*  bitmap_background; // bitmap to show thru mask
  GColor    mask_color; //color of the mask
  GColor    background_color; // color of the background
  char*     text; // text used for mask (when when masking by text)
  GFont     font; // font used for text mask;
  GTextOverflowMode text_overflow; // overflow used for text mask;
  GTextAlignment  text_align; // alignment used for text masks
} EffectMask;  

typedef struct {
  time_t  starttt; // time_t at the first refresh
  uint16_t  startms; // ms at the first refresh
  uint32_t  frame; // frame number
} EffectFPS;  

typedef void effect_cb(GContext* ctx, GRect position, void* param);

// inverter effect.
// Added by Yuriy Galanter
effect_cb effect_invert;

// vertical mirror effect.
// Added by Yuriy Galanter
effect_cb effect_mirror_vertical;


// horizontal mirror effect.
// Added by Yuriy Galanter
effect_cb effect_mirror_horizontal;

// Rotate 90 degrees
// Added by Ron64
// Parameter: true: rotate right/clockwise false: rotate left/counter_clockwise
effect_cb effect_rotate_90_degrees;

// blur effect.
// Added by Grégoire Sage
// Parameter: blur radius
effect_cb effect_blur;

// Zoom effect
// Added by Ron64
// Parameter: Y zoom (high byte) X zoom(low byte),  0x10 no zoom 0x20 200% 0x08 50%, 
// use the percentage macro EL_ZOOM(150,60). In this example: Y- zomm in 150%, X- zoom out to 60% 
effect_cb effect_zoom;

#define EL_ZOOM(x,y) ((void*)((((y)*16/100)|(((x)*16/100)<<8))))

// Lens effect
// Added by Ron64
// Parameters: lens focal(high byte) and object distance(low byte)
effect_cb effect_lens;

#define EL_LENS(f,d) ((void*) ( d|(f<<8)))


// mask effect.
// Added by Yuriy Galanter
// see struct effect_mask for parameter description
effect_cb effect_mask;

// Just displays the average FPS of the app
// Probably works better on a fullscreen effect layer so it can catch all redraw messages
effect_cb effect_fps;