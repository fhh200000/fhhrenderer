#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include "../algorithm/ray.h"
typedef struct {
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
} camera;
camera new_camera(vec3 lookfrom,vec3 lookat,vec3 vup,float vfov,float aspect);
ray camera_get_ray(camera* this,float u,float v);
#endif // CAMERA_H_INCLUDED
