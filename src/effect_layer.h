#pragma once
#pragma once
  
#include <pebble.h>  


typedef struct {
	Layer       *layer;
  uint8_t effect;
} EffectLayer;


EffectLayer* effect_layer_create(GRect frame);

void effect_layer_destroy(EffectLayer *effect_layer);

Layer* effect_layer_get_layer(EffectLayer *effect_layer);