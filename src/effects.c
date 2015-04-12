#include <pebble.h>
#include "effects.h"
#include "math.h"

// set pixel color at given coordinates 
void set_pixel(uint8_t *bitmap_data, int bytes_per_row, int y, int x, uint8_t color) {
  
  uint8_t (*fb_a)[bytes_per_row] = (uint8_t (*)[bytes_per_row])bitmap_data;
  
  #ifdef PBL_COLOR 
    fb_a[y][x] = color; // in Basalt - simple set entire byte
  #else
    fb_a[y][x / 8] ^= (-color ^ fb_a[y][x / 8]) & (1 << (x % 8)); // in Aplite - set the bit
  #endif
}




// get pixel color at given coordinates 
uint8_t get_pixel(uint8_t *bitmap_data, int bytes_per_row, int y, int x) {
  
  uint8_t (*fb_a)[bytes_per_row] = (uint8_t (*)[bytes_per_row])bitmap_data;
  
  #ifdef PBL_COLOR
    return fb_a[y][x]; // in Basalt - simple get entire byte
  #else
    return (fb_a[y][x / 8] >> (x % 8)) & 1; // in Aplite - get the bit
  #endif
}
  
  

// inverter effect.
void effect_invert(uint8_t *bitmap_data, int bytes_per_row, GRect position, void* param) {
  
  for (int y = 0; y < position.size.h; y++)
     for (int x = 0; x < position.size.w; x++)
        #ifdef PBL_COLOR // on Basalt simple doing NOT on entire returned byte/pixel
          set_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x, ~get_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x));
        #else // on Aplite since only 1 and 0 is returning, doing "not" by 1 - pixel
          set_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x, 1 - get_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x));
        #endif
}

// vertical mirror effect.
void effect_mirror_vertical(uint8_t *bitmap_data, int bytes_per_row, GRect position, void* param) {
  uint8_t temp_pixel;  

  for (int y = 0; y < position.size.h / 2 ; y++)
     for (int x = 0; x < position.size.w; x++){
        temp_pixel = get_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x);
        set_pixel(bitmap_data, bytes_per_row, y + position.origin.y, x + position.origin.x, get_pixel(bitmap_data, bytes_per_row, position.origin.y + position.size.h - y - 2, x + position.origin.x));
        set_pixel(bitmap_data, bytes_per_row, position.origin.y + position.size.h - y - 2, x + position.origin.x, temp_pixel);
     }
}


// horizontal mirror effect.
void effect_mirror_horizontal(uint8_t *bitmap_data, int bytes_per_row, GRect position, void* param) {
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
// Parameter:  true: rotate right/clockwise,  false: rotate left/counter_clockwise
void effect_rotate_90_degrees(uint8_t *bitmap_data, int bytes_per_row, GRect position, void* param){
  bool right = (bool)(uint32_t)param;
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


// Zoom effect.
// Added by Ron64
// Parameter: Y zoom (high byte) X zoom(low byte),  0x10 no zoom 0x20 200% 0x08 50%, 
// use the percentage macro EL_ZOOM(150,60). In this example: Y- zoom in 150%, X- zoom out to 60% 
void effect_zoom(uint8_t *bd, int bpr, GRect position, void* param){
  uint8_t xCn, yCn, Y1,X1, ratioY, ratioX;
  xCn= position.origin.x + position.size.w /2;
  yCn= position.origin.y + position.size.h /2;

  ratioY= (int32_t)param >>8 & 0xFF;
  ratioX= (int32_t)param & 0xFF;

  for (int y = 0; y <= position.size.h>>1; y++)
    for (int x = 0; x <= position.size.w>>1; x++)
    {
      //yS,xS scan source: centre to out or out to centre
      int8_t yS = (ratioY>16) ? (position.size.h/2)- y: y; 
      int8_t xS = (ratioX>16) ? (position.size.w/2)- x: x;
      Y1= (yS<<4) /ratioY;
      X1= (xS<<4) /ratioX;
      set_pixel(bd,bpr, yCn +yS, xCn +xS, get_pixel(bd,bpr, yCn +Y1, xCn +X1)); 
      set_pixel(bd,bpr, yCn +yS, xCn -xS, get_pixel(bd,bpr, yCn +Y1, xCn -X1));
      set_pixel(bd,bpr, yCn -yS, xCn +xS, get_pixel(bd,bpr, yCn -Y1, xCn +X1));
      set_pixel(bd,bpr, yCn -yS, xCn -xS, get_pixel(bd,bpr, yCn -Y1, xCn -X1));
    }
//Todo: Should probably reduce Y size on zoom out or limit reading beyond edge of screen.
}

// Lens effect.
// Added by Ron64
// Parameters: lens focal(high byte) and object distance(low byte)
void effect_lens(uint8_t *bd, int bpr, GRect position, void* param){
  uint8_t d,r, xCn, yCn;

  xCn= position.origin.x + position.size.w /2;
  yCn= position.origin.y + position.size.h /2;
  d=position.size.w;
  if (position.size.h < d)
    d= position.size.h;
  r= d/2; // radius of lens
  float focal =   (int32_t)param >>8 & 0xFF;// focal point of lens
  float obj_dis = (int32_t)param & 0xFF;//distance of object from focal point.
  
  for (int y = r; y >= 0; --y)
    for (int x = r; x >= 0; --x)
      if (x*x+y*y < r*r)
      {
        int Y1= my_tan(my_asin(y/focal))*obj_dis;
        int X1= my_tan(my_asin(x/focal))*obj_dis;
        set_pixel(bd,bpr, yCn +y, xCn +x, get_pixel(bd,bpr, yCn +Y1, xCn +X1)); 
        set_pixel(bd,bpr, yCn +y, xCn -x, get_pixel(bd,bpr, yCn +Y1, xCn -X1));
        set_pixel(bd,bpr, yCn -y, xCn +x, get_pixel(bd,bpr, yCn -Y1, xCn +X1));
        set_pixel(bd,bpr, yCn -y, xCn -x, get_pixel(bd,bpr, yCn -Y1, xCn -X1));
      }
//Todo: Change to lock-up arcsin table in the future. (Currently using floating point math library that is relatively big & slow)
}