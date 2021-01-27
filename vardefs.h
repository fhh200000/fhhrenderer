#ifndef VARDEF_H
#define VARDEF_H
//必要的头文件信息。
#include <stdlib.h>
//基本数据类型的定义。
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef unsigned long long U64;
//决定图像的宽高。
#define WIDTH 1280
#define HEIGHT 720
//定义抗锯齿重采样次数。
#define SAMPLE 64

//决定我们是否将渲染结果显示在屏幕上。
#define DISPLAY_ON_SCREEN
//定义像素格式类型。显示在屏幕上的格式与输出像素格式不同。
typedef struct {
        U8 b;
        U8 g;
        U8 r;
} __attribute__((packed)) screen_pixel;
typedef struct {
        U8 r;
        U8 g;
        U8 b;
} __attribute__((packed)) file_pixel;
#ifdef DISPLAY_ON_SCREEN
//如果需要显示在屏幕上，则使用glut。
#include <GL/glut.h>
typedef screen_pixel pixel;
#else
//如果不显示，则包含3rdparty，用于输出png文件。
#include "3rdparty/stb_image_write.h"
//定义像素格式类型。
typedef file_pixel pixel;
#endif
//指定线程个数。
#define THREADS 8
//如果是Linux，使用pthread库创建多线程
#ifdef __linux__
#include <pthread.h>
#else
#error "No available thread library found.We can only use Linux pthreads."
#endif
typedef struct{
    U8 r;
    U8 g;
    U8 b;
    U8 a;
} __attribute__((packed)) svg_pixel;
//如果评委认为不能够加载SVG，则不使用第三方库。
#define LOADING_SVG_IS_NOT_ALLOWED
#ifndef LOADING_SVG_IS_NOT_ALLOWED
#include "3rdparty/nanosvgrast.h"
#endif
#endif
