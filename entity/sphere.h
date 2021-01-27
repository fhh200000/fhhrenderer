#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED
#include "../algorithm/hitable.h"
#include <math.h>
//定义球体的结构体类型。
typedef struct {
    hitable first;
    vec3 center;
    float r;
    material* mat;
} sphere;

sphere new_sphere(vec3 center,float r,material* mat);
U8 sphere_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec);
#endif // SPHERE_H_INCLUDED
