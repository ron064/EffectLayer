#include <pebble.h>
#include "effect_layer.h"
#include "effects.h"  
  
// on layer update - apply effect
static void effect_layer_update_proc(Layer *me, GContext* ctx) {
 
  // retreiving layer and its coordinates
	EffectLayer* effect_layer = *(EffectLayer**)(layer_get_data(me));
	GRect layer_frame = layer_get_frame(me);  
  
  //capturing framebuffer bitmap into matix[WINDOWS_HEIGHT x WINDOWS_WIDTH]
  GBitmap *fb = graphics_capture_frame_buffer_format(ctx, GBitmapFormat8Bit);
  uint8_t (*fb_matrix)[WINDOW_WIDTH] = (uint8_t (*)[WINDOW_WIDTH]) gbitmap_get_data(fb);
  
  switch (effect_layer->effect) {
    
    case EFFECT_INVERT:
      effect_invert(fb_matrix, layer_frame);
      break;
    
    case EFFECT_MIRROR_VERTICAL:
      effect_mirror_vertical(fb_matrix, layer_frame);
      break;
    
    case EFFECT_MIRROR_HORIZONTAL:
      effect_mirror_horizontal(fb_matrix, layer_frame);
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
