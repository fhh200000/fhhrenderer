#ifndef METAL_H_INCLUDED
#define METAL_H_INCLUDED
#include "../algorithm/hitable.h"
#include "../algorithm/reflect.h"
#include "../algorithm/texture.h"
typedef struct {
    material first;
    texture* albedo;
    float fuzz;
} metal;
U8 metal_scatter(material* super,ray* r_in,hit_record* rec,vec3* attenuation, ray* scattered);
metal new_metal(texture* albedo,float fuzz);


#endif // METAL_H_INCLUDED
