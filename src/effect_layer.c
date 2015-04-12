#include <pebble.h>
#include "effect_layer.h"
#include "effects.h"  
  
// on layer update - apply effect
static void effect_layer_update_proc(Layer *me, GContext* ctx) {
 
  // retrieving layer and its coordinates
  EffectLayer* effect_layer = (EffectLayer*)(layer_get_data(me));
  GRect layer_frame = layer_get_frame(me);  
  
  //capturing framebuffer bitmap into matrix[WINDOWS_HEIGHT x WINDOWS_WIDTH]
  GBitmap *fb = graphics_capture_frame_buffer(ctx);
  uint8_t *bitmap_data =  gbitmap_get_data(fb);
  int bytes_per_row = gbitmap_get_bytes_per_row(fb);
  
  // Applying effects
  for(uint8_t i=0; effect_layer->effects[i] && i<MAX_EFFECTS;++i) effect_layer->effects[i](bitmap_data, bytes_per_row, layer_frame, effect_layer->params[i]);

  graphics_release_frame_buffer(ctx, fb);
}
  

// create effect layer
EffectLayer* effect_layer_create(GRect frame) {
    
  //creating base layer
  Layer* layer =layer_create_with_data(frame, sizeof(EffectLayer));
  layer_set_update_proc(layer, effect_layer_update_proc);
  EffectLayer* effect_layer = (EffectLayer*)layer_get_data(layer);
  memset(effect_layer,0,sizeof(EffectLayer));
  effect_layer->layer = layer;

  return effect_layer;                    
}

//destroy effect layer
void effect_layer_destroy(EffectLayer *effect_layer) {
  layer_destroy(effect_layer->layer);
}

// returns base layer
Layer* effect_layer_get_layer(EffectLayer *effect_layer){
  return effect_layer->layer;
}

//sets effect for the layer
void effect_layer_add_effect(EffectLayer *effect_layer, effect_cb* effect, void* param) {
  if(effect_layer->next_effect<MAX_EFFECTS) {
    effect_layer->effects[effect_layer->next_effect] = effect;
    effect_layer->params[effect_layer->next_effect] = param;  
    ++effect_layer->next_effect;
  }
}
