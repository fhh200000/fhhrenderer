#include "checker_texture.h"
checker_texture new_checker_texture(texture* odd,texture* even)
{
    checker_texture checker_texture;
    checker_texture.first.value = checker_texture_value;
    checker_texture.odd = odd;
    checker_texture.even = even;
    return checker_texture;
}
vec3 checker_texture_value(texture* super,float u,float v,vec3* p)
{
    checker_texture* this = (checker_texture*) super;
    float sine = sin(10*p->e0)*sin(10*p->e1)*sin(10*p->e2);
    return (sine<0)?(this->odd->value(this->odd,u,v,p)):(this->even->value(this->even,u,v,p));
}
