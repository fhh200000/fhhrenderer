#ifndef IMAGE_TEXTURE_H_INCLUDED
#define IMAGE_TEXTURE_H_INCLUDED
#include "../vardefs.h"
#include "../algorithm/texture.h"
typedef struct {
    texture first;
    int width,height;
    svg_pixel* pixel;
    vec3 base_color;
} image_texture;
image_texture new_image_texture(int width,int height,svg_pixel* pixel,vec3 base_color);
vec3 image_texture_value(texture* super,float u,float v,vec3* p);
#endif // IMAGE_TEXTURE_H_INCLUDED
