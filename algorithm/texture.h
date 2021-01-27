#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include "vec3.h"
struct texture {
    vec3 (*value)(struct texture* super,float u,float v,vec3* p);
};
typedef struct texture texture;
#endif // TEXTURE_H_INCLUDED
