#ifndef CYLINDER_H_INCLUDED
#define CYLINDER_H_INCLUDED
#include "../algorithm/hitable.h"
//定义柱体类型。
typedef struct {
    hitable first;
    vec3 center;
    float radius;
    int facing;
    float height;
} cylinder;
cylinder new_cylinder(vec3 center,float radius,int facing,float height);
U8 cylinder_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec);

#endif // CYLINDER_H_INCLUDED
