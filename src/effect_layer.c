#include <pebble.h>
#include "effect_layer.h"
#include "effects.h"  
  
// on layer update - apply effect
static void effect_layer_update_proc(Layer *me, GContext* ctx) {
  // retreiving layer and its coordinates
	EffectLayer* effect_layer = *(EffectLayer**)(layer_get_data(me));
	GRect layer_frame = layer_get_frame(me);  
  
  //capturing framebuffer bitmap
  GBitmap *fb = graphics_capture_frame_buffer_format(ctx, GBitmapFormat8Bit);
  GRect window_dim = gbitmap_get_bounds(fb);
  uint8_t *fb_data = gbitmap_get_data(fb);
  
  switch (effect_layer->effect) {
    
    case EFFECT_INVERT:
      effect_invert(fb_data,  layer_frame.origin.x,  layer_frame.origin.y, layer_frame.size.h, layer_frame.size.w, window_dim.size.w);
      break;
    
    case EFFECT_MIRROR:
      effect_mirror(fb_data,  layer_frame.origin.x,  layer_frame.origin.y, layer_frame.size.h, layer_frame.size.w, window_dim.size.w);
      break;
    
  }
  
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
