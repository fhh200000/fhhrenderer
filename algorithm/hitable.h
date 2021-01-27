#ifndef HITABLE_H
#define HITABLE_H
#include "ray.h"
#include "../vardefs.h"

typedef struct hitable hitable;
struct material;
typedef struct {
    float t,u,v;
    vec3 p;
    vec3 normal;
    struct material* mat_ptr;
} hit_record;
struct hitable {
    U8 (*hit)(struct hitable* super,ray* r,float t_min,float t_max,hit_record* rec);
};
struct material {
    U8 (*scatter)(struct material* super,ray* r_in,hit_record* rec,vec3* attenuation, ray* scattered);
    hitable* obj;
};
typedef struct material material;



#endif // HITABLE_H
