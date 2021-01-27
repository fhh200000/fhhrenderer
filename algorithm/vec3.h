#ifndef VEC3_H
#define VEC3_H

//包含数学库。
#include <math.h>
//定义三维向量的数据结构。
typedef struct {
    float e0,e1,e2;
} vec3;
//三维向量的构造函数。
vec3 new_vec3(float e0,float e1,float e2);
//三维向量的基本运算公式。
vec3 vec3_add(vec3* a,vec3* b);
vec3 vec3_sub(vec3* a,vec3* b);
vec3 vec3_mul(vec3* a,vec3* b);
float vec3_length(vec3* in);
float vec3_squared_length(vec3* in);
vec3 vec3_unit_vector(vec3* in);
float vec3_dot(vec3* a,vec3* b);
vec3 vec3_cross(vec3* a,vec3* b);
vec3 vec3_mul_times(vec3* a,float factor);
vec3 vec3_div_times(vec3* a,float factor);
#endif
