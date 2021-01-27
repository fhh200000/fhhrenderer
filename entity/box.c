#include "box.h"
box new_box(vec3 p0,vec3 p1,material* mat)
{
    box box;
    box.pmin = p0;
    box.pmax = p1;
    box.first.hit = box_hit;
    void* temp;
    xy_rectangle* s0 = malloc(sizeof(xy_rectangle));
    *s0 = new_xy_rectangle(p0.e0,p1.e0,p0.e1,p1.e1,p1.e2,mat);
    box.surfaces[0] = (hitable*)s0;


    temp = malloc(sizeof(xy_rectangle));
    *(xy_rectangle*)temp = new_xy_rectangle(p0.e0,p1.e0,p0.e1,p1.e1,p0.e2,mat);
    invert_normal* s1 = malloc(sizeof(invert_normal));
    *s1 = new_invert_normal((hitable*)temp);
    box.surfaces[1] = (hitable*)s1;

    xz_rectangle* s2 = malloc(sizeof(xz_rectangle));
    *s2 = new_xz_rectangle(p0.e0,p1.e0,p0.e2,p1.e2,p1.e1,mat);
    box.surfaces[2] = (hitable*)s2;

    temp = malloc(sizeof(xz_rectangle));
    *(xz_rectangle*)temp = new_xz_rectangle(p0.e0,p1.e0,p0.e2,p1.e2,p0.e1,mat);
    invert_normal* s3 = malloc(sizeof(invert_normal));
    *s3 = new_invert_normal((hitable*)temp);
    box.surfaces[3] = (hitable*)s3;

    yz_rectangle* s4 = malloc(sizeof(yz_rectangle));
    *s4 = new_yz_rectangle(p0.e1,p1.e1,p0.e2,p1.e2,p1.e0,mat);
    box.surfaces[4] = (hitable*)s4;

    temp = malloc(sizeof(yz_rectangle));
    *(yz_rectangle*)temp = new_yz_rectangle(p0.e1,p1.e1,p0.e2,p1.e2,p0.e0,mat);
    invert_normal* s5 = malloc(sizeof(invert_normal));
    *s5 = new_invert_normal((hitable*)temp);
    box.surfaces[5] = (hitable*)s5;
    return box;
}
U8 box_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec)
{
    hit_record temp_rec;
    U8 hit_anything = 0;
    float closest = t_max;
    box* this = (box*)super;
    for(int i=0;i<6;i++)
    {
        if(this->surfaces[i]->hit(this->surfaces[i],r,t_min,closest,&temp_rec))
        {
            hit_anything = 1;
            closest = temp_rec.t;
            *rec = temp_rec;
        }
    }
    return hit_anything;
}
