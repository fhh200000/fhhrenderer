#ifndef RAY_H
#define RAY_H

#include "../vardefs.h"
#include "vec3.h"
//对光线类的定义。
typedef struct {
    vec3 origin;
    vec3 direction;
} ray;
vec3 point_at_parameter(ray* source,float factor);
vec3 random_in_unit_sphere();
#endif // RAY_H
