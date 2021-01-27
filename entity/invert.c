#include "invert.h"
invert_normal new_invert_normal(hitable* in)
{
    invert_normal invert_normal;
    invert_normal.first.hit = invert_normal_hit;
    invert_normal.p = in;
    return invert_normal;
}
U8 invert_normal_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec)
{
    invert_normal* this = (invert_normal*) super;
    if(this->p->hit(this->p,r,t_min,t_max,rec))
    {
        rec->normal = vec3_mul_times(&(rec->normal),-1);
        return 1;
    }
    return 0;
}
