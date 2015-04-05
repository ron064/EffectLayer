#pragma once
#include <pebble.h>  

//list of supported effects
#define EFFECT_INVERT 1
#define EFFECT_MIRROR_VERTICAL 2
#define EFFECT_MIRROR_HORIZONTAL 4
#define EFFECT_ROTATE_RIGHT 8
#define EFFECT_ROTATE_LEFT 16

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