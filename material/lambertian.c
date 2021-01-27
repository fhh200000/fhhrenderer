#include "lambertian.h"
lambertian new_lamberatian(texture* albedo)
{
    lambertian lambertian;
    lambertian.albedo = albedo;
    lambertian.first.scatter =lambertian_scatter;
    return lambertian;
}
U8 lambertian_scatter(material* super,ray* r_in,hit_record* rec,vec3* attenuation, ray* scattered)
{
    lambertian* this = (lambertian*)super;
    vec3 target = random_in_unit_sphere();
    target = vec3_add(&target,&(rec->p));
    target = vec3_add(&target,&(rec->normal));
    ray result = {rec->p,vec3_sub(&target,&(rec->p))};
    *scattered = result;
    *attenuation = this->albedo->value(this->albedo,rec->u,rec->v,&(rec->p));
    return 1;
}
