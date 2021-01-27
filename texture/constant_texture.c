#include "constant_texture.h"
constant_texture new_constant_texture(vec3 color)
{
    constant_texture constant_texture;
    constant_texture.first.value = constant_texture_value;
    constant_texture.color = color;
    return constant_texture;
}
vec3 constant_texture_value(texture* super,float u,float v,vec3* p)
{
    constant_texture* this = (constant_texture*)super;
    return this->color;
}
