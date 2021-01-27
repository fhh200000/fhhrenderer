#ifndef REFRACT_H_INCLUDED
#define REFRACT_H_INCLUDED
#include "../vardefs.h"
#include "vec3.h"
U8 refract(vec3* v,vec3* n,float ni_over_nt,vec3* refracted);
#endif // REFRACT_H_INCLUDED
