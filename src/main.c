#include <pebble.h>
#include "effect_layer.h"

Window *my_window;
TextLayer *text_layer1, *text_layer2, *text_layer3, *text_layer4;
PropertyAnimation *anim;

EffectLayer* effect_layer;
EffectMask *mask;

GRect anim_finish[4] = {{{75,2}, {68,80}}, {{75,87}, {68,80}}, {{40,87}, {68,80}}, {{2,2},{68,80}}};
int anim_count = -1;

// on animation stop callback create next animation
void next_anim();
void on_animation_stopped(Animation *anim, bool finished, void *ctx)
{
  next_anim();
}

void next_anim() {
  
  anim_count++;
  if (anim_count == 4)  anim_count = 0; // if we finished all animation points - start from the beginning
  
  #ifndef PBL_COLOR // Aplite doesn't automatically destroy animation, we need to do it
    if (anim)  property_animation_destroy(anim);
  #endif
  
  anim = property_animation_create_layer_frame(effect_layer_get_layer(effect_layer), NULL, &anim_finish[anim_count]);
  
  AnimationHandlers handlers = {
     .stopped = (AnimationStoppedHandler) on_animation_stopped
  };
  animation_set_handlers((Animation*) anim, handlers, NULL);
    
  animation_set_curve((Animation*) anim, AnimationCurveLinear);
  animation_set_duration((Animation*) anim, 1500);
  animation_set_delay((Animation*) anim, 0);
  animation_schedule((Animation*) anim);
  
}

// utility function to create text layers
void create_color_layer(TextLayer *text_layer, GRect coords, char text[], GColor color, GColor bgcolor) {
  
  text_layer = text_layer_create(coords);
  text_layer_set_font(text_layer,fonts_get_system_font(FONT_KEY_ROBOTO_BOLD_SUBSET_49));
  text_layer_set_text(text_layer, text);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_text_color(text_layer, color);
  text_layer_set_background_color(text_layer, bgcolor);
  layer_add_child(window_get_root_layer(my_window), text_layer_get_layer(text_layer));
  
}

void handle_init(void) {
  my_window = window_create();
  window_set_background_color(my_window, GColorBlack);
  window_stack_push(my_window, true);
  
  //creating colorful field (not doing this while testing MASK effect)
  /*#ifdef PBL_COLOR
    create_color_layer(text_layer1, GRect(0,0,72,84), "11", GColorYellow, GColorRed);
    create_color_layer(text_layer1, GRect(73,0, 72,84), "22", GColorCyan, GColorBlue);
    create_color_layer(text_layer1, GRect(0,85,72,84), "44", GColorWhite, GColorBlack);
    create_color_layer(text_layer1, GRect(73,85,72,84), "66", GColorMintGreen, GColorDarkGreen);
  #else
    create_color_layer(text_layer1, GRect(0,0,72,84), "11",  GColorBlack, GColorWhite);
    create_color_layer(text_layer1, GRect(73,0, 72,84), "22", GColorWhite, GColorBlack);
    create_color_layer(text_layer1, GRect(0,85,72,84), "44", GColorWhite, GColorBlack);
    create_color_layer(text_layer1, GRect(73,85,72,84), "66", GColorBlack, GColorWhite);
  #endif */
  
  //creating effect layer
  effect_layer = effect_layer_create(GRect(2,2,68,80));
  
  // ** { begin setup mask for MASK effect
  mask = malloc(sizeof(EffectMask));

  mask->text = NULL; // not using text
  mask->bitmap_mask = gbitmap_create_with_resource(RESOURCE_ID_MASK_SHAPE); // using bitmap mask instead
    
  mask->font = fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD);
  mask->background_color = GColorBlack;
  mask->mask_color = GColorWhite;
  mask->text_align = GTextAlignmentCenter;
  mask->text_overflow = GTextOverflowModeWordWrap;
  
  mask->bitmap_background = gbitmap_create_with_resource(RESOURCE_ID_MASK_BG);
  // ** end setup mask }

//  effect_layer_add_effect(effect_layer, effect_mirror_vertical, NULL);
//  effect_layer_add_effect(effect_layer, effect_rotate_90_degrees, (void*)true);
//  effect_layer_add_effect(effect_layer, effect_mirror_vertical, NULL);
//  effect_layer_add_effect(effect_layer, effect_mirror_horizontal, NULL);
//  effect_layer_add_effect(effect_layer, effect_blur, (void*)1);
//  effect_layer_add_effect(effect_layer, effect_lens, EL_LENS((68-2)*2/3, (68-2)*4/9));
//  effect_layer_add_effect(effect_layer, effect_zoom, EL_ZOOM(200,60));
  effect_layer_add_effect(effect_layer, effect_mask, mask);
  
  layer_add_child(window_get_root_layer(my_window), effect_layer_get_layer(effect_layer));
  
  //begin animation
  next_anim();
  
}

void handle_deinit(void) {
  
  //clearning MASK
  gbitmap_destroy(mask->bitmap_mask);
  gbitmap_destroy(mask->bitmap_background);
  free(mask);
  
  text_layer_destroy(text_layer1);
  text_layer_destroy(text_layer1);
  text_layer_destroy(text_layer2);
  text_layer_destroy(text_layer3);
  
  effect_layer_destroy(effect_layer);
  
  window_destroy(my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
