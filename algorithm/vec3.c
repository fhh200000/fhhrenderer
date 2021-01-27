//此处实现三维向量的基本运算。
//手动面向对象（滑稽）
#include "vec3.h"
inline vec3 new_vec3(float e0,float e1,float e2)
{
    vec3 result = {e0,e1,e2};
    return result;
}
inline vec3 vec3_add(vec3* a,vec3* b)
{
    vec3 result={a->e0+b->e0,a->e1+b->e1,a->e2+b->e2};
    return result;
}
inline vec3 vec3_sub(vec3* a,vec3* b)
{
    vec3 result={a->e0-b->e0,a->e1-b->e1,a->e2-b->e2};
    return result;
}
inline vec3 vec3_mul(vec3* a,vec3* b)
{
    vec3 result={a->e0*b->e0,a->e1*b->e1,a->e2*b->e2};
    return result;
}
inline float vec3_length(vec3* in)
{
    return sqrt(vec3_squared_length(in));
}
inline float vec3_squared_length(vec3* in)
{
    return in->e0*in->e0 + in->e1*in->e1 + in->e2*in->e2;
}
inline vec3 vec3_unit_vector(vec3* in)
{
    float length = vec3_length(in);
    vec3 result = {in->e0/length,in->e1/length,in->e2/length};
    return result;
}
inline float vec3_dot(vec3* a,vec3* b)
{
    return a->e0*b->e0 + a->e1*b->e1 + a->e2*b->e2;
}
inline vec3 vec3_cross(vec3* a,vec3* b)
{
    vec3 result = {(a->e1*b->e2 - a->e2*b->e1),-(a->e0*b->e2 - a->e2*b->e0),(a->e0*b->e1 - a->e1*b->e0)};
    return result;
}
inline vec3 vec3_mul_times(vec3* a,float factor)
{
    vec3 result={a->e0*factor,a->e1*factor,a->e2*factor};
    return result;
}
inline vec3 vec3_div_times(vec3* a,float factor)
{
    vec3 result={a->e0/factor,a->e1/factor,a->e2/factor};
    return result;
}
