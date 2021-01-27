#ifndef LAMBERTIAN_H_INCLUDED
#define LAMBERTIAN_H_INCLUDED
#include "../algorithm/hitable.h"
#include "../algorithm/texture.h"
typedef struct {
    material first;
    texture* albedo;
} lambertian;
U8 lambertian_scatter(material* super,ray* r_in,hit_record* rec,vec3* attenuation, ray* scattered);
lambertian new_lamberatian(texture* albedo);
#endif // LAMBERTIAN_H_INCLUDED
