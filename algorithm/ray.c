#include "ray.h"
vec3 point_at_parameter(ray* source,float factor)
{
    vec3 scaled_vec = vec3_mul_times(&(source->direction),factor);
    return vec3_add(&(source->origin),&scaled_vec);
}
vec3 random_in_unit_sphere()
{
    vec3 p;
    static vec3 unit={1,1,1};
    do
    {
        p.e0 = drand48();
        p.e1 = drand48();
        p.e2 = drand48();
        p = vec3_mul_times(&p,2.0);
        p = vec3_sub(&p,&unit);
    }
    while(vec3_squared_length(&p) >=1.0);
    return p;
}
