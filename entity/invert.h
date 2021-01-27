#ifndef INVERT_H_INCLUDED
#define INVERT_H_INCLUDED
#include "../algorithm/hitable.h"
typedef struct {
    hitable first;
    hitable* p;
}invert_normal;
invert_normal new_invert_normal(hitable* in);
U8 invert_normal_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec);

#endif // INVERT_H_INCLUDED
