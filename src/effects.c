#include <pebble.h>
#include "effects.h"
  
// set pixel color at given coordinates 
void set_pixel(uint8_t *bitmap_data, int bytes_per_row, int y, int x, uint8_t color) {
  
  uint8_t (*fb_a)[bytes_per_row] = (uint8_t (*)[bytes_per_row])bitmap_data;
  
  #ifdef PBL_COLOR 
    fb_a[y][x] = color; // in Basalt - simple set entire byte
  #else
    fb_a[y][x / 8] ^= (-color ^ fb_a[y][x / 8]) & (1 << (x % 8)); // in Applite - set the bit
  #endif
}




// get pixel color at given coordinates 
uint8_t get_pixel(uint8_t *bitmap_data, int bytes_per_row, int y, int x) {
  
  uint8_t (*fb_a)[bytes_per_row] = (uint8_t (*)[bytes_per_row])bitmap_data;
  
  #ifdef PBL_COLOR
    return fb_a[y][x]; // in Basalt - simple get entire byte
  #else
    return (fb_a[y][x / 8] >> (x % 8)) & 1; // in Applite - get the bit
  #endif
}
  
  

// inverter effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer  
void effect_invert(uint8_t *bitmap_data, int bytes_per_row, GRect position) {
  
  for (int y = 0; y < position.size.h; y++)
     for (int x = 0; x < position.size.w; x++)
        #ifdef PBL_COLOR // on Basalt simple doing NOT on entire returned byte/pixel
          set_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x, ~get_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x));
        #else // on applite since only 1 and 0 is returning, doing "not" by 1 - pixel
          set_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x, 1 - get_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x));
        #endif
              
          
}

// vertical mirror effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_mirror_vertical(uint8_t *bitmap_data, int bytes_per_row, GRect position) {
  uint8_t temp_pixel;  

  for (int y = 0; y < position.size.h / 2 ; y++)
     for (int x = 0; x < position.size.w; x++){
        temp_pixel = get_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x);
        set_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x, get_pixel(bitmap_data, bytes_per_row, position.origin.y + position.size.h - y - 2, x + position.origin.x));
        set_pixel(bitmap_data, bytes_per_row, position.origin.y + position.size.h - y - 2, x + position.origin.x, temp_pixel);
     }
}


// horizontal mirror effect.
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
void effect_mirror_horizontal(uint8_t *bitmap_data, int bytes_per_row, GRect position) {
  uint8_t temp_pixel;  

  for (int y = 0; y < position.size.h; y++)
     for (int x = 0; x < position.size.w / 2; x++){
        temp_pixel = get_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x);
        set_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x, get_pixel(bitmap_data, bytes_per_row, y + position.origin.y, position.origin.x + position.size.w - x - 2));
        set_pixel(bitmap_data, bytes_per_row, y + position.origin.y, position.origin.x + position.size.w - x - 2, temp_pixel);
     }
}

// Rotate 90 degrees
// Added by Ron64
// fb_a: matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH] width screen bitmap data
// position: x,y,h,w of the layer
// right true: rotate right/clockwise false: rotate left/counter_clockwise
void effect_rotate_90_degrees(uint8_t *bitmap_data, int bytes_per_row, GRect position, bool right){
  uint8_t qtr, xCn, yCn, temp_pixel;
  xCn= position.origin.x + position.size.w /2;
  yCn= position.origin.y + position.size.h /2;
  qtr=position.size.w;
  if (position.size.h < qtr)
    qtr= position.size.h;
  qtr= qtr/2;

  for (int c1 = 0; c1 < qtr; c1++)
    for (int c2 = 1; c2 < qtr; c2++){
      temp_pixel = get_pixel(bitmap_data, bytes_per_row, yCn +c1, xCn +c2);
      if (right){
        set_pixel(bitmap_data, bytes_per_row, yCn +c1, xCn +c2, get_pixel(bitmap_data, bytes_per_row, yCn -c2, xCn +c1));
        set_pixel(bitmap_data, bytes_per_row, yCn -c2, xCn +c1, get_pixel(bitmap_data, bytes_per_row, yCn -c1, xCn -c2));
        set_pixel(bitmap_data, bytes_per_row, yCn -c1, xCn -c2, get_pixel(bitmap_data, bytes_per_row, yCn +c2, xCn -c1));
        set_pixel(bitmap_data, bytes_per_row, yCn +c2, xCn -c1, temp_pixel);
      }
      else{
        set_pixel(bitmap_data, bytes_per_row, yCn +c1, xCn +c2, get_pixel(bitmap_data, bytes_per_row, yCn +c2, xCn -c1));
        set_pixel(bitmap_data, bytes_per_row, yCn +c2, xCn -c1, get_pixel(bitmap_data, bytes_per_row, yCn -c1, xCn -c2));
        set_pixel(bitmap_data, bytes_per_row, yCn -c1, xCn -c2, get_pixel(bitmap_data, bytes_per_row, yCn -c2, xCn +c1));
        set_pixel(bitmap_data, bytes_per_row, yCn -c2, xCn +c1, temp_pixel);
      }
     }
}