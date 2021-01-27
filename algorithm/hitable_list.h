#ifndef HITABLE_LIST_H_INCLUDED
#define HITABLE_LIST_H_INCLUDED
#include "hitable.h"
extern hitable** hitable_list;
extern int hitable_list_count;
U8 hitable_list_hit(ray* r,float t_min,float t_max,hit_record* rec);
#endif // HITABLE_LIST_H_INCLUDED
