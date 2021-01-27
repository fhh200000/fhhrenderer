#ifndef GLASS_H_INCLUDED
#define GLASS_H_INCLUDED
#include "../algorithm/ray.h"
#include "../algorithm/hitable.h"
#include "../algorithm/reflect.h"
#include "../algorithm/refract.h"
typedef struct {
    material first;
    vec3 attenuation;
    float refract_idx;
} glass;
glass new_glass(vec3 attenuation,float refract_idx);
U8 glass_scatter(material* super,ray* r_in,hit_record* rec,vec3* attenuation, ray* scattered);
#endif // GLASS_H_INCLUDED
