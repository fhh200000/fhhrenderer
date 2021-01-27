#include "glass.h"
glass new_glass(vec3 attenuation,float refract_idx)
{
    glass glass;
    glass.attenuation = attenuation;
    glass.refract_idx = refract_idx;
    glass.first.scatter = glass_scatter;
    return glass;
}
float schlick(float cosine,float refract_idx)
{
    float r0 = (1-refract_idx) / (1+refract_idx);
    r0 = r0 * r0;
    return r0+(1-r0)*pow((1-cosine),5);
}
U8 glass_scatter(material* super,ray* r_in,hit_record* rec,vec3* attenuation, ray* scattered)
{
    glass* this = (glass*) super;
    vec3 outward_normal;
    vec3 reflected = reflect(&(r_in->direction),&(rec->normal));
    float ni_over_nt;
    *attenuation = this->attenuation;
    vec3 refracted;
    float reflect_prob;
    float cosine;
    if(vec3_dot(&(r_in->direction),&(rec->normal))>0)
    {
        outward_normal = vec3_mul_times(&(rec->normal),-1);
        ni_over_nt = this->refract_idx;
        cosine = this->refract_idx * vec3_dot(&(r_in->direction),&(rec->normal)) / vec3_length(&(r_in->direction));
    }
    else
    {
        outward_normal = rec->normal;
        ni_over_nt = 1.0 / this->refract_idx;
        cosine = vec3_dot(&(r_in->direction),&(rec->normal)) / vec3_length(&(r_in->direction)) * -1;
    }
    if(refract(&(r_in->direction),&outward_normal,ni_over_nt,&refracted))
    {
        reflect_prob = schlick(cosine,this->refract_idx);
    }
    else
    {
        ray r = {rec->p,reflected};
        *scattered = r;
        reflect_prob = 1.0;
    }
    if(drand48() < reflect_prob)
    {
        ray r = {rec->p,reflected};
        *scattered = r;
    }
    else
    {
         ray r = {rec->p,refracted};
        *scattered = r;
    }
    return 1;
}
