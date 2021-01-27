#include "reflect.h"
vec3 reflect(vec3* v,vec3* n)
{
    vec3 result = vec3_mul_times(n,2*vec3_dot(v,n));
    result = vec3_sub(v,&result);
    return result;
}
