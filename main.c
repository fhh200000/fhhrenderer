#define STB_IMAGE_WRITE_IMPLEMENTATION
#define NANOSVGRAST_IMPLEMENTATION
#define NANOSVG_IMPLEMENTATION
#include "main.h"
//存储像素信息。
pixel* pixeldata;
//存储贴图。
texture* map_texture;
//定义世界的坐标。
vec3 lookfrom={2.7,4.0,2.0};
vec3 lookat={0.0,0.2,-1.2};
vec3 vup={0.0,1.0,0.0};
//定义相机。
camera cam;
//为了让用户能够在屏幕上看到实时信息，在渲染了一定数量的数据后，通知界面更新。
static int progress=-10;
static int finished_thread = 0;
void draw_pixel()
{
    progress += 10;
    printf("\rRendering:%2.2f%% finished.",(float)(progress-finished_thread*10)/HEIGHT*100);
}

//定义渲染颜色的函数。
vec3 color(ray* r,int depth)
{
    static vec3 black ={0,0,0};
    hit_record rec;
    if(hitable_list_hit(r,0.001,FLT_MAX,&rec))
    {

        ray scattered;
        vec3 attenuation;
        if(depth<50&&rec.mat_ptr->scatter(rec.mat_ptr,r,&rec,&attenuation,&scattered))
        {
            vec3 result = color(&scattered,depth+1);
            return vec3_mul(&attenuation,&result);
        }
        else //追踪超过最大深度
        {
            return black;
        }
    }
    //没有击中任何一个物体，返回蓝色的背景。
    vec3 unit = vec3_unit_vector(&(r->direction));
    float t = 0.5*(unit.e1+1.0);
    //复用unit
    unit.e0 = 1;
    unit.e1 = 1;
    unit.e2 = 1;
    unit.e2 = 1;
    vec3 raw = vec3_mul_times(&unit,(1.0-t));
    unit.e0 = 0.5;
    unit.e1 = 0.7;
    unit.e2 = 1.0;
    vec3 light = vec3_mul_times(&unit,t);
    return vec3_add(&raw,&light);

}
#ifdef DISPLAY_ON_SCREEN
void disp_init(int argc,char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow("渲染预览窗口");
    glutDisplayFunc(draw_pixel);
    printf("Display init done.\n");
    render();
    glutMainLoop();
}
#endif

int main(int argc,char** argv)
{
    setvbuf(stdout,NULL,_IONBF,0);//禁用输出缓存。
    printf("fhh renderer: v1.01 Loading...\n");
    pixeldata = (pixel*)malloc(WIDTH*HEIGHT*sizeof(pixel));
    #ifdef DISPLAY_ON_SCREEN
    disp_init(argc,argv);
    #else
    render();
    //OpenGL的行顺序与png中不同，此处给出修复。
    int length_of_a_line = WIDTH*sizeof(pixel);
    pixel* temp_pixel = (pixel*)malloc(HEIGHT*length_of_a_line);
    for(int i=0;i<HEIGHT;i++)
    {
        memcpy(temp_pixel+(HEIGHT-1-i)*WIDTH,pixeldata+i*WIDTH,length_of_a_line);
    }
    printf("\n3rdparty/stb_image_write:writing image to output.png.\n");
    stbi_write_png("output.png",WIDTH,HEIGHT,3,temp_pixel,length_of_a_line);
    free(temp_pixel);
    #endif
    free(pixeldata);
}
void render(void)
{
    printf("Creating world...\n");
    hitable_list_count = 6;
    //加载主贴图。
    load_texture();
    //创建世界。----------------------------------------------------------------------------
    hitable** list = malloc(sizeof(hitable*)*hitable_list_count);
    hitable_list = list;
    //物体1：玻璃球。
    vec3 center_sphere1 = {0,0,-0.8};
    vec3 color_glass = {1.0,1.0,1.0};
    glass glass_sphere = new_glass(color_glass,1.5);
    sphere sphere1 = new_sphere(center_sphere1,0.45,(material*)&glass_sphere);
    hitable_list[0] = (hitable*)&sphere1;
    //物体2：背景。
    vec3 center_sphere2 = {0,-100.5,-1};
    constant_texture texture_sphere2_color1 = new_constant_texture(new_vec3(0.9,0.9,0.9));
    constant_texture texture_sphere2_color2 = new_constant_texture(new_vec3(0.2,0.3,0.1));
    checker_texture texture_sphere2 = new_checker_texture((texture*)&texture_sphere2_color1,(texture*)&texture_sphere2_color2);
    lambertian lambertian_sphere = new_lamberatian((texture*)&texture_sphere2);
    sphere sphere2 = new_sphere(center_sphere2,100,(material*)&lambertian_sphere);
    hitable_list[1] = (hitable*)&sphere2;
    //物体3：金属球。
    vec3 center_sphere3 = {-0.9,0,-0.8};
    constant_texture texture_sphere3 = new_constant_texture(new_vec3(0.8,0.6,0.2));
    metal metal_sphere = new_metal((texture*)&texture_sphere3,0.1);
    sphere sphere3 = new_sphere(center_sphere3,0.45,(material*)&metal_sphere);
    hitable_list[2] = (hitable*)&sphere3;
    //物体4：漫反射球。
    vec3 center_sphere4 = {0.9,0,-0.8};
    constant_texture texture_sphere4 = new_constant_texture(new_vec3(0.9,0.9,0.9));
    lambertian lambertian_sphere4 = new_lamberatian((texture*)&texture_sphere4);
    sphere sphere4 = new_sphere(center_sphere4,0.45,(material*)&lambertian_sphere4);
    hitable_list[3] = (hitable*)&sphere4;
    //物体5：漫反射Logo盒子。
    lambertian lambertian_box1 = new_lamberatian(map_texture);
    box box1 = new_box(new_vec3(-1.2,-0.5,-3),new_vec3(-0.2,0.5,-2),(material*)&lambertian_box1);
    hitable_list[4] = (hitable*)&box1;
    //物体6：金属材质Logo盒子。
    image_texture texture_box2;
    memcpy(&texture_box2,map_texture,sizeof(image_texture));
    texture_box2.base_color = new_vec3(0.8,0.8,0.8);
    metal metal_box2 = new_metal((texture*)&texture_box2,0.05);
    box box2 = new_box(new_vec3(0.2,-0.5,-3),new_vec3(1.2,0.5,-2),(material*)&metal_box2);
    hitable_list[5] = (hitable*)&box2;
    //------------------------------------------------------------------------------------
    //创建相机。
    cam = new_camera(lookfrom,lookat,vup,30,(float)WIDTH/(float)HEIGHT);
    //计算线程的头尾。
    printf("Using %d threads for render process.\nRegion map:\n",THREADS);
    thread_render_data data[THREADS];
    int thread_length = HEIGHT / THREADS;
    pthread_t threads[THREADS];
    for(int i=0;i<THREADS;i++)
    {
        //创建线程。
        data[i].begin = i*thread_length;
        data[i].end   = (i+1)*thread_length;
        printf("Thread %d:line %d-%d...\n",i,data[i].begin,data[i].end);
        pthread_create(&threads[i],NULL,thread_render,&data[i]);
    }
    static int prev_progress;
    prev_progress = progress;
    while(1)
    {
        usleep(10000);
        if(prev_progress!=progress)
        {
            prev_progress = progress;
            #ifdef DISPLAY_ON_SCREEN
            glDrawPixels(WIDTH,HEIGHT,GL_BGR_EXT,GL_UNSIGNED_BYTE,pixeldata);
            glFlush();
            #endif
        }
        if(finished_thread==THREADS)
            break;
    }
    //等待。
    for(int i=0;i<THREADS;i++)
    {
        pthread_join(threads[i],NULL);
    }
    //最后，输出结果。
    #ifdef DISPLAY_ON_SCREEN
    glDrawPixels(WIDTH,HEIGHT,GL_BGR_EXT,GL_UNSIGNED_BYTE,pixeldata);
    #endif
}
void* thread_render(void* arg)
{
    int begin,end;
    begin=((thread_render_data*)arg)->begin;
    end=((thread_render_data*)arg)->end;
    pixel* curr_pixel = pixeldata+begin*WIDTH;
    //主渲染函数。
    for(int i=begin;i<end;i++)
    {
        for(int j=0;j<WIDTH;j++)
        {
            vec3 col = {0,0,0};
            for(int s=0;s<SAMPLE;s++)
            {
                float u = (float)(j+drand48())/(float)WIDTH;
                float v = (float)(i+drand48())/(float)HEIGHT;
                ray r = camera_get_ray(&cam,u,v);
                vec3 result = color(&r,0);
                col = vec3_add(&col,&result);
            }
            col = vec3_div_times(&col,SAMPLE);
            //调整图像的Gamma。
            col.e0 = sqrt(col.e0);
            col.e1 = sqrt(col.e1);
            col.e2 = sqrt(col.e2);
            curr_pixel->r = (U8)(255.99*col.e0);
            curr_pixel->g = (U8)(255.99*col.e1);
            curr_pixel->b = (U8)(255.99*col.e2);
            curr_pixel++;
        }
        if(!(i%10))
        {
            draw_pixel();
        }
    }
    draw_pixel();
    finished_thread++;
    pthread_exit(NULL);
}
void load_texture()
{
    printf("Loading texture...\n");
    #ifndef LOADING_SVG_IS_NOT_ALLOWED
    nanosvg_debug("Loading svg from logo.svg.\n");
	NSVGimage *image;
	NSVGrasterizer *rast;
	int w, h;
	const char* filename = "logo.svg";
	image = nsvgParseFromFile(filename, "px", 96.0f);
	if (image == NULL) {
		nanosvg_debug("Could not open SVG image.\n");
		return;
	}
	w = (int)image->width;
	h = (int)image->height;
    nanosvg_debug("Got image,width:%d,height:%d.\n",w,h);
	rast = nsvgCreateRasterizer();
	if (rast == NULL) {
		nanosvg_debug("Could not init rasterizer.\n");
		goto clean;
	}
    svg_pixel* svg_image = malloc(w*h*sizeof(svg_pixel));
    nsvgRasterize(rast, image, 0,0,1, (U8*)svg_image, w, h, w*4);
    image_texture* main_texture=malloc(sizeof(image_texture));
    *main_texture = new_image_texture(w,h,svg_image,new_vec3(1.0,1.0,1.0));
    map_texture = (texture*) main_texture;
clean:
    nsvgDeleteRasterizer(rast);
	nsvgDelete(image);
    #else
    printf("WARNING:LOADING SVG IS NOT ALLOWED.\n");
    constant_texture* colors = malloc(sizeof(constant_texture)*2);
    colors[0] = new_constant_texture(new_vec3(0.4,0.4,0.4));
    colors[1] = new_constant_texture(new_vec3(0.95,0.95,0.95));
    checker_texture* main_texture = malloc(sizeof(checker_texture));
    *main_texture = new_checker_texture((texture*)&(colors[0]),(texture*)&(colors[1]));
    map_texture = (texture*) main_texture;
    #endif
}
