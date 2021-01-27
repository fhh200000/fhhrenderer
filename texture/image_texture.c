#include "image_texture.h"
image_texture new_image_texture(int width,int height,svg_pixel* pixel,vec3 base_color)
{
    image_texture image_texture;
    image_texture.first.value = image_texture_value;
    image_texture.height = height;
    image_texture.width  = width;
    image_texture.pixel  = pixel;
    image_texture.base_color = base_color;
    return image_texture;
}
vec3 image_texture_value(texture* super,float u,float v,vec3* p)
{
    image_texture* this = (image_texture*)super;
    int xpos = (int)(u*this->width);
    int ypos = (int)((1-v)*this->height);
    if(xpos<0)
        xpos = 0;
    if(xpos>this->width)
        xpos = this->width;
    if(ypos<0)
        ypos = 0;
    if(ypos>this->height)
        ypos = this->height;
    svg_pixel data = (this->pixel[ypos*this->width+xpos]);
    float transparency = data.a / 255.0; //0~255
    vec3 result;
    result.e0 = (data.r / 255.0) * transparency + this->base_color.e0*(1-transparency);
    result.e1 = (data.g / 255.0) * transparency + this->base_color.e1*(1-transparency);
    result.e2 = (data.b / 255.0) * transparency + this->base_color.e2*(1-transparency);
    return result;
}
