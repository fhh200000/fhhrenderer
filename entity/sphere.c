#include "sphere.h"
sphere new_sphere(vec3 center,float r,material* mat)
{
    sphere s;
    s.first.hit = sphere_hit;
    s.center = center;
    s.r = r;
    s.mat = mat;
    return s;
}
void sphere_get_uv(vec3* in,float* u,float* v)
{
    float phi = atan2(in->e2,in->e0);
    float theta = asin(in->e1);
    *u = 1-(phi+M_PI)/(2*M_PI);
    *v = (theta+M_PI/2)/M_PI;
}
U8 sphere_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec)
{
    sphere* this = (sphere*)super;
    vec3 oc = vec3_sub(&(r->origin),&(this->center));
    float a = vec3_dot(&(r->direction),&(r->direction));
    float b = vec3_dot(&(oc),&(r->direction));
    float c = vec3_dot(&oc,&oc)-this->r * this->r;
    float discriminant = b*b - a*c;
    if(discriminant > 0)
    {
        float temp = (-b - sqrt(b*b-a*c))/a;
        if(temp<t_max&&temp>t_min)
        {
            rec->t = temp;
            rec->p = point_at_parameter(r,temp);
            float u,v;
            vec3 temp = vec3_sub(&(rec->p),&(this->center));
            temp = vec3_div_times(&temp,this->r);
            sphere_get_uv(&temp,&u,&v);
            rec->u = u;
            rec->v = v;
            vec3 tmp = vec3_sub(&(rec->p),&(this->center));
            rec->normal = vec3_div_times(&tmp,this->r);
            rec->mat_ptr = this->mat;
            return 1;
        }
        temp = (-b + sqrt(b*b-a*c))/a;
        if(temp<t_max&&temp>t_min)
        {
            rec->t = temp;
            rec->p = point_at_parameter(r,temp);
            vec3 tmp = vec3_sub(&(rec->p),&(this->center));
            rec->normal = vec3_div_times(&tmp,this->r);
            rec->mat_ptr = this->mat;
            return 1;
        }
    }
    return 0;
}

