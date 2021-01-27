#include "camera.h"
camera new_camera(vec3 lookfrom,vec3 lookat,vec3 vup,float vfov,float aspect)
{
    camera result;
    vec3 u,v,w,tmp;
    float theta = vfov*M_PI / 180;
    float half_height = tan(theta/2);
    float half_width = aspect * half_height;
    result.origin = lookfrom;
    w = vec3_sub(&lookfrom,&lookat);
    w = vec3_unit_vector(&w);
    u = vec3_cross(&vup,&w);
    u = vec3_unit_vector(&u);
    v = vec3_cross(&w,&u);
    vec3 lower_left_corner = vec3_mul_times(&u,half_width);
    lower_left_corner = vec3_sub(&lookfrom,&lower_left_corner);
    tmp = vec3_mul_times(&v,half_height);
    lower_left_corner = vec3_sub(&lower_left_corner,&tmp);
    lower_left_corner = vec3_sub(&lower_left_corner,&w);
    result.lower_left_corner = lower_left_corner;
    result.horizontal = vec3_mul_times(&u,2*half_width);
    result.vertical = vec3_mul_times(&v,2*half_height);
    return result;
}
ray camera_get_ray(camera* this,float u,float v)
{
    vec3 u_horizontal = vec3_mul_times(&(this->horizontal),u);
    vec3 v_vertical   = vec3_mul_times(&(this->vertical),v);
    vec3 direction    = vec3_add(&u_horizontal,&v_vertical);
    direction = vec3_add(&direction,&(this->lower_left_corner));
    direction = vec3_sub(&direction,&(this->origin));
    ray result = {this->origin,direction};
    return result;
}
