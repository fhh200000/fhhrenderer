#include "rectangle.h"
xy_rectangle new_xy_rectangle(float x1,float x2,float y1,float y2,float t,material* mat)
{
    xy_rectangle xy_rectangle;
    xy_rectangle.first.hit = xy_rectangle_hit;
    xy_rectangle.x1 = x1;
    xy_rectangle.y1 = y1;
    xy_rectangle.x2 = x2;
    xy_rectangle.y2 = y2;
    xy_rectangle.t  = t;
    xy_rectangle.mat= mat;
    return xy_rectangle;
}
U8 xy_rectangle_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec)
{
    xy_rectangle* this = (xy_rectangle*) super;
    float t = (this->t-r->origin.e2) / r->direction.e2;
    if(t<t_min||t>t_max)
        return 0;
    float x = r->origin.e0 + t*r->direction.e0;
    float y = r->origin.e1 + t*r->direction.e1;
    if(x<this->x1 || x>this->x2 || y<this->y1 || y>this->y2)
        return 0;
    rec->u = (x - this->x1)/(this->x2-this->x1);
    rec->v = (y - this->y1)/(this->y2-this->y1);
    rec->t = t;
    rec->mat_ptr = this->mat;
    rec->p = point_at_parameter(r,t);
    rec->normal = new_vec3(0,0,1);
    return 1;
}

xz_rectangle new_xz_rectangle(float x1,float x2,float z1,float z2,float t,material* mat)
{
    xz_rectangle xz_rectangle;
    xz_rectangle.first.hit = xz_rectangle_hit;
    xz_rectangle.x1 = x1;
    xz_rectangle.z1 = z1;
    xz_rectangle.x2 = x2;
    xz_rectangle.z2 = z2;
    xz_rectangle.t  = t;
    xz_rectangle.mat= mat;
    return xz_rectangle;
}
U8 xz_rectangle_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec)
{
    xz_rectangle* this = (xz_rectangle*) super;
    float t = (this->t-r->origin.e1) / r->direction.e1;
    if(t<t_min||t>t_max)
        return 0;
    float x = r->origin.e0 + t*r->direction.e0;
    float z = r->origin.e2 + t*r->direction.e2;
    if(x<this->x1 || x>this->x2 || z<this->z1 || z>this->z2)
        return 0;
    rec->u = (x - this->x1)/(this->x2-this->x1);
    rec->v = (z - this->z1)/(this->z2-this->z1);
    rec->t = t;
    rec->mat_ptr = this->mat;
    rec->p = point_at_parameter(r,t);
    rec->normal = new_vec3(0,1,0);
    return 1;
}

yz_rectangle new_yz_rectangle(float y1,float y2,float z1,float z2,float t,material* mat)
{
    yz_rectangle yz_rectangle;
    yz_rectangle.first.hit = yz_rectangle_hit;
    yz_rectangle.y1 = y1;
    yz_rectangle.z1 = z1;
    yz_rectangle.y2 = y2;
    yz_rectangle.z2 = z2;
    yz_rectangle.t  = t;
    yz_rectangle.mat= mat;
    return yz_rectangle;
}
U8 yz_rectangle_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec)
{
    yz_rectangle* this = (yz_rectangle*) super;
    float t = (this->t-r->origin.e0) / r->direction.e0;
    if(t<t_min||t>t_max)
        return 0;
    float y = r->origin.e1 + t*r->direction.e1;
    float z = r->origin.e2 + t*r->direction.e2;
    if(y<this->y1 || y>this->y2 || z<this->z1 || z>this->z2)
        return 0;
    rec->v = (y - this->y1)/(this->y2-this->y1);
    rec->u = 1.0-((z - this->z1)/(this->z2-this->z1));
    rec->t = t;
    rec->mat_ptr = this->mat;
    rec->p = point_at_parameter(r,t);
    rec->normal = new_vec3(1,0,0);
    return 1;
}

