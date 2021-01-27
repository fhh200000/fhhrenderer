#include "cylinder.h"
cylinder new_cylinder(vec3 center,float radius,int facing,float height)
{
    hitable h={cylinder_hit};
    cylinder c={h,center,radius,facing,height};
    return c;
}
U8 cylinder_hit(hitable* super,ray* r,float t_min,float t_max,hit_record* rec)
{
    cylinder* this = (cylinder*) super;
    //圆柱体计算公式：（Vx^2+m^2Vy^2）t^2+2(SxVx+m^2SyVy)t+(Sx^2+m^2Sy^2-r^2)=0
    vec3 vx = {r->direction.e0,0,0};
    vec3 vy = {0,r->direction.e1,0};
    vec3 sx = {r->origin.e0,0,0};
    vec3 sy = {0,r->origin.e1,0};
    float a = vec3_dot(&vx,&vx) + vec3_dot(&vy,&vy);
    float b = vec3_dot(&sx,&vx) + vec3_dot(&sy,&vy); //此处是1/2b
    float c = vec3_dot(&sx,&sx) + vec3_dot(&sy,&sy) - this->radius * this->radius;
    //以下是抄来的。
     float discriminant = b*b - a*c;
    if(discriminant > 0)
    {
        float temp = (-b - sqrt(b*b-a*c))/a;
        if(temp<t_max&&temp>t_min)
        {
            rec->t = temp;
            rec->p = point_at_parameter(r,temp);
            vec3 tmp = vec3_sub(&(rec->p),&(this->center));
            rec->normal = vec3_div_times(&tmp,this->radius);
            return 1;
        }
        temp = (-b + sqrt(b*b-a*c))/a;
        if(temp<t_max&&temp>t_min)
        {
            rec->t = temp;
            rec->p = point_at_parameter(r,temp);
            vec3 tmp = vec3_sub(&(rec->p),&(this->center));
            rec->normal = vec3_div_times(&tmp,this->radius);
            return 1;
        }
    }
    return 0;
    //以上。
}
