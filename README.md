<b>EffectLayer</b> is a visual effect layer for Pebble Smartwatch. User places the layer over screen at set coordinates and special effects are applied to that area of the screen. Effects work both on Aplite/Classic Pebble and Basalt/Pebble time unless specified (e.g. Blur works only on Basalt)

To use the library place the source files in your SRC directory and add <code>#include "effect_layer.h"</code> to your source. EffectLayer library is implemented in efficient pay-to-play way so only effects that you actualy use get compiled into your binary.

Currently supported effects:
<ul>
<li>Invert</li>
<li>Vertical Mirror</li>
<li>Horizontal Mirror</li>
<li>Rotate 90 degrees (counter- or clock-wise</li>
<li>Blur</li>
<li>Zoom</li>
<li>Lens</li>
<li>Mask</li>
<li>FPS</li>
</ul>
<hr>
<h3>Functions</h3>

<code>EffectLayer* effect_layer_create(GRect frame)</code> - creates effect layer and returns pointer to it. Parameter is GRect with coordinates and layer size, for example <code>EffectLayer* effect_layer_create(GRect(0, 0, 144, 168));</code> will cover entire screen

<code>void effect_layer_destroy(EffectLayer *effect_layer)</code> - destroys effect layer and frees memory.

<code>Layer* effect_layer_get_layer(EffectLayer *effect_layer)</code> - gets underlying Layer of the effect layer for basic manipulations such as addin to Window root layer or layer's changing frame or bounds

<code>void effect_layer_add_effect(EffectLayer *effect_layer, effect_cb* effect, void* param)</code> - adds effect to the layer. Parameters are - effect layer that you created previously, name of the function to perform effect, optional data to pass to the effect. User can call this function multiple times on the same effect layer, adding multiple effects, so there's no need to create multiple layers. At this time library has following built in effect functions to represent the effects listed above:
<ul>
<li>effect_invert</li>
<li>effect_mirror_vertical</li>
<li>effect_mirror_horizontal</li>
<li>effect_rotate_90_degrees</li>
<li>effect_blur</li>
<li>effect_zoom</li>
<li>effect_lens</li>
<li>effect_mask</li>
<li>effect_fps</li>
</ul>

<h3>Usage</h3>

<code>effect_layer_add_effect(my_effect_layer, effect_invert, NULL);</code> - adds inverter effect
 
<code>effect_layer_add_effect(my_effect_layer, effect_mirror_vertical, NULL);</code> - adds vertical mirror effect 

<code>effect_layer_add_effect(my_effect_layer, effect_mirror_horizontal, NULL);</code> - adds horizontal mirror effect

<code>effect_layer_add_effect(my_effect_layer, effect_rotate_90_degrees, (void *)true);</code> - rotates 90 degrees counterclockwise

<code>effect_layer_add_effect(my_effect_layer, effect_rotate_90_degrees, (void *)false);</code> - rotates 90 degrees
clockwise

<code>effect_layer_add_effect(my_effect_layer, effect_blur, (void *)my_radius);</code> - Creates blur effect (on Basalt/Pebble Time only), where my_radius is uint_8t radius of the blur.

<code>effect_layer_add_effect(my_effect_layer, effect_zoom, EL_ZOOM(x,y));</code> - Zooms screen area under layer by x and y

<code>effect_layer_add_effect(my_effect_layer, effect_lens, EL_LENS(f,d));</code> - Applies Lens effect, where f & d are focal distance of the lens and distane to object respectfully.

<code>effect_layer_add_effect(my_effect_layer, effect_mask, mask);</code> - Applies Mask, achieving various transparency effects. See <a href="http://codecorner.galanter.net/2015/04/15/mask-effect-for-effectlayer-for-pebble/" target="_blank">this article</a> on usage examples.

<code>effect_layer_add_effect(my_effect_layer, effect_fps, EffectFPS);</code> - displays average FPS of the app

<h3>Extentions</h3>

Library is user-extendable, if you define your function in format

<code>void effect_my_own_cool_effect(GContext* ctx, GRect position, void* param) { /* cool effect code */ }</code>

you can add it to EffectLayer in maner similar to above:

<code>effect_layer_add_effect(my_effect_layer, effect_my_own_cool_effect, param);</code> 
