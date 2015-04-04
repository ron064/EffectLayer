#pragma once
#include <pebble.h>  

//list of supported effects
#define EFFECT_INVERT 1
#define EFFECT_MIRROR_VERTICAL 2    
#define EFFECT_MIRROR_HORIZONTAL 3      
#define EFFECT_RORATE_RIGHT 4
#define EFFECT_RORATE_LEFT 5

// structure of effect layer
typedef struct {
  Layer       *layer;
  uint8_t effect;
} EffectLayer;


//creates effect layer
EffectLayer* effect_layer_create(GRect frame);

//destroys effect layer
void effect_layer_destroy(EffectLayer *effect_layer);

//sets effect for the layer
void effect_layer_set_effect(EffectLayer *effect_layer, int effect);

//gets layer
Layer* effect_layer_get_layer(EffectLayer *effect_layer);