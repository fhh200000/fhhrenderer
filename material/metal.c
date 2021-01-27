#include "metal.h"
U8 metal_scatter(material* super,ray* r_in,hit_record* rec,vec3* attenuation, ray* scattered)
{
    metal* this = (metal*)super;
    vec3 reflected = vec3_unit_vector(&(r_in->direction));
    reflected = reflect(&reflected,&(rec->normal));
    vec3 fuzz = random_in_unit_sphere();
    fuzz = vec3_mul_times(&fuzz,this->fuzz);
    ray s = {rec->p,vec3_add(&reflected,&fuzz)};
    *scattered = s;
    *attenuation = this->albedo->value(this->albedo,rec->u,rec->v,&(rec->p));
    return (vec3_dot(&(scattered->direction),&(rec->normal))>0);
}
metal new_metal(texture* albedo,float fuzz)
{
    metal metal;
    metal.albedo = albedo;
    metal.first.scatter =metal_scatter;
    metal.fuzz = fuzz>1.0f?1.0f:fuzz;
    return metal;
}
