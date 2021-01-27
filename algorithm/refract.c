#include "refract.h"
U8 refract(vec3* v,vec3* n,float ni_over_nt,vec3* refracted)
{
    vec3 unit_v = vec3_unit_vector(v);
    float dt = vec3_dot(&unit_v,n);
    float discriminant = 1.0-ni_over_nt*ni_over_nt*(1-dt*dt);
    if(discriminant>0)
    {
        vec3 result = vec3_mul_times(n,dt);
        result = vec3_sub(&unit_v,&result);
        result = vec3_mul_times(&result,ni_over_nt);
        vec3 temp = vec3_mul_times(n,sqrt(discriminant));
        *refracted = vec3_sub(&result,&temp);
        return 1;
    }
    return 0;
}
