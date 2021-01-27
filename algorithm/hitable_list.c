#include "hitable_list.h"

hitable** hitable_list;
int hitable_list_count;
U8 hitable_list_hit(ray* r,float t_min,float t_max,hit_record* rec)
{
    hit_record temp_rec;
    U8 hit_anything = 0;
    float closest = t_max;
    for(int i=0;i<hitable_list_count;i++)
    {
        if(hitable_list[i]->hit(hitable_list[i],r,t_min,closest,&temp_rec))
        {
            hit_anything = 1;
            closest = temp_rec.t;
            *rec = temp_rec;
        }
    }
    return hit_anything;
}
