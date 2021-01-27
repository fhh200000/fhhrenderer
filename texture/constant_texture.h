#ifndef CONSTANT_TEXTURE_H_INCLUDED
#define CONSTANT_TEXTURE_H_INCLUDED
#include "../algorithm/texture.h"
typedef struct {
    texture first;
    vec3 color;
} constant_texture;
constant_texture new_constant_texture(vec3 color);
vec3 constant_texture_value(texture* super,float u,float v,vec3* p);
#endif // CONSTANT_TEXTURE_H_INCLUDED
