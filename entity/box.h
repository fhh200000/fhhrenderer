#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED
#include "../algorithm/hitable.h"
#include "rectangle.h"
#include "invert.h"
typedef struct {
    hitable first;
    vec3 pmin;
    vec3 pmax;
    hitable* surfaces[6];
    material* material;
} box;
box new_box(vec3 p0,vec3 p1,material* mat);
U8 box_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec);
#endif // BOX_H_INCLUDED
