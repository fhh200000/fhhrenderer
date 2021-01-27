#ifndef MAIN_H
#define MAIN_H
#include "algorithm/vec3.h"
#include "algorithm/ray.h"
#include "algorithm/hitable_list.h"
#include "entity/sphere.h"
#include "entity/rectangle.h"
#include "entity/camera.h"
#include "entity/box.h"
#include "material/metal.h"
#include "material/lambertian.h"
#include "material/glass.h"
#include "texture/constant_texture.h"
#include "texture/checker_texture.h"
#include "texture/image_texture.h"
#include <stdio.h>
#include <float.h>
#define _XOPEN_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#define nanosvg_debug(x...) printf("3rdparty/nanosvg:" x)
void draw_pixels(void);
void disp_init(int argc,char** argv);
void render(void);
vec3 color(ray* r,int depth);
void random_scene();
void* thread_render(void* arg);
void load_texture();
typedef struct {
    int begin;
    int end;
} thread_render_data;
#endif // MAIN_H
