#include <pebble.h>
#include "effects.h"

void effect_invert(uint8_t *fb_data, int x, int y, int h, int w, int window_w) {
  
  // original position in framebuffer bitmap
  int j = y * window_w + x; 
  
   // looping thru layer dimentions
  for (int i=0; i < h * w ; i++) {
    
    fb_data[j] = ~fb_data[j];
    
    // advancing to next point OR next line
    if (i !=0 && i % w  == 0) {
       j += window_w - w + 1;
    } else {
       j++;
    }
     
  }  
  
}



void effect_mirror(uint8_t *fb_data, int x, int y, int h, int w, int window_w) {
  
  // original position in framebuffer bitmap
  int j = y * window_w + x; 
  
  int mirror_address = (y + h) * window_w + x + w;
  uint8_t temp_pixel;
    
  // looping thru layer dimentions
  for (int i=0; i < h * (w + 1)  / 2  ; i++) {
 
    temp_pixel = fb_data[j];
    fb_data[j] = fb_data[mirror_address];
    fb_data[mirror_address] = temp_pixel;
    
    // advancing to next point OR next line
    if (i !=0 && i % w  == 0) {
       j += window_w - w + 1;
       mirror_address -= (window_w - w + 1);
    } else {
       j++;
       mirror_address--;
    }
     
  }  
  
}