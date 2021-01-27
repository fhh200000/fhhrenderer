#ifndef CHECKER_TEXTURE_H_INCLUDED
#define CHECKER_TEXTURE_H_INCLUDED
#include "../algorithm/texture.h"
typedef struct {
    texture first;
    texture* odd; //奇数时的材质
    texture* even; //偶数时的材质
} checker_texture;
checker_texture new_checker_texture(texture* odd,texture* even);
vec3 checker_texture_value(texture* super,float u,float v,vec3* p);

#endif // CHECKER_TEXTURE_H_INCLUDED
