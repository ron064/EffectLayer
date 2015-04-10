#include <pebble.h>
#include "effect_layer.h"
#include "effects.h"  
  
// on layer update - apply effect
static void effect_layer_update_proc(Layer *me, GContext* ctx) {
 
  // retreiving layer and its coordinates
  EffectLayer* effect_layer = *(EffectLayer**)(layer_get_data(me));
  GRect layer_frame = layer_get_frame(me);  
  
  //capturing framebuffer bitmap into matix[WINDOWS_HEIGHT x WINDOWS_WIDTH]
  GBitmap *fb = graphics_capture_frame_buffer(ctx);
  uint8_t *bitmap_data =  gbitmap_get_data(fb);
  int bytes_per_row = gbitmap_get_bytes_per_row(fb);
  
  if (EFFECT_INVERT & effect_layer->effect)
      effect_invert(bitmap_data, bytes_per_row, layer_frame);
    
  if (EFFECT_MIRROR_VERTICAL & effect_layer->effect)
      effect_mirror_vertical(bitmap_data, bytes_per_row, layer_frame);
    
  if (EFFECT_MIRROR_HORIZONTAL & effect_layer->effect)
      effect_mirror_horizontal(bitmap_data, bytes_per_row, layer_frame);

  if (EFFECT_ROTATE_RIGHT & effect_layer->effect)
      effect_rotate_90_degrees(bitmap_data, bytes_per_row, layer_frame, true);

  if (EFFECT_ROTATE_LEFT & effect_layer->effect)
      effect_rotate_90_degrees(bitmap_data, bytes_per_row, layer_frame, false);
    
  if (EFFECT_BLUR & effect_layer->effect)
    effect_blur(bitmap_data, bytes_per_row, layer_frame, 2);

  graphics_release_frame_buffer(ctx, fb);
  
}
  

// create effect layer
EffectLayer* effect_layer_create(GRect frame) {
    
  //creating base layer
  EffectLayer* effect_layer = malloc(sizeof(EffectLayer));
  effect_layer->layer = layer_create_with_data(frame, sizeof(EffectLayer*));
  layer_set_update_proc(effect_layer->layer, effect_layer_update_proc);
  memcpy(layer_get_data(effect_layer->layer), &effect_layer, sizeof(EffectLayer*));

  //initially assiging "invert" effect
  effect_layer->effect = EFFECT_INVERT;

  return effect_layer;                    

}

//destroy effect layer
void effect_layer_destroy(EffectLayer *effect_layer) {
  
  layer_destroy(effect_layer->layer);
  free(effect_layer);

}

// returns base layer
Layer* effect_layer_get_layer(EffectLayer *effect_layer){
  return effect_layer->layer;
}

//sets effect for the layer
void effect_layer_set_effect(EffectLayer *effect_layer, int effect) {
   effect_layer->effect = effect;
}
