#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED
#include "../algorithm/hitable.h"
typedef struct {
    hitable first;
    float x1,y1,x2,y2,t;
    material* mat;
} xy_rectangle;
xy_rectangle new_xy_rectangle(float x1,float x2,float y1,float y2,float t,material* mat);
U8 xy_rectangle_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec);

typedef struct {
    hitable first;
    float x1,z1,x2,z2,t;
    material* mat;
} xz_rectangle;
xz_rectangle new_xz_rectangle(float x1,float x2,float z1,float z2,float t,material* mat);
U8 xz_rectangle_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec);

typedef struct {
    hitable first;
    float y1,z1,y2,z2,t;
    material* mat;
} yz_rectangle;
yz_rectangle new_yz_rectangle(float x1,float x2,float z1,float z2,float t,material* mat);
U8 yz_rectangle_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec);
#endif // RECTANGLE_H_INCLUDED
