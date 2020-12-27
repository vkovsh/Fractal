#include "fractal.h"

t_colordepth    g_colordepth;

t_retcode    init_fractal(const t_fractaltype ftype,
            const GLuint height,
            const GLuint width,
            const size_t iterations)
{
    if (height > MAX_HEIGHT ||
        width > MAX_WIDTH)
    {
        return (RC_ERR_BAD_FRACTAL_IMAGE_SIZE);
    }
    
    {
        g_f->type = ftype;
        g_f->height = height;
        g_f->width = width;
        g_fractalarray->pixels_addr = (GLuint *)malloc(width * height * sizeof(GLuint));
        if (g_fractalarray->pixels_addr == NULL)
        {
            return (RC_ERR_BAD_MEMALLOC);
        }
        g_fractalarray->pixels_array = (GLuint **)malloc(height * sizeof(GLuint *));
        if (g_fractalarray->pixels_array == NULL)
        {
            return (RC_ERR_BAD_MEMALLOC);
        }
        for (GLuint i = 0; i < height; ++i)
        {
            g_fractalarray->pixels_array[i] = g_fractalarray->pixels_addr + i * width;
        }
    }
    g_f->x_0 = 0;
    g_f->y_0 = 0;
    g_f->x_pos = 0;
    g_f->y_pos = 0;
    g_f->iterations = iterations;
    if (g_f->type == MANDELBROT)
    {
        g_f->checker = &in_mandelbrot;
    }
    else
    {
        g_f->checker = &in_julia;
    }
    
    g_f->scale = g_f->width / 4;
    g_colordepth.depth_b = 6;
    g_colordepth.depth_g = 6;
    g_colordepth.depth_r = 6;
    return (RC_SUCSESS);
}

//TODO
t_retcode   init_gl(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    int g_window_id = glutCreateWindow("Fractal");
    //glutDestroyWindow(g_window_id);
    
    return (RC_SUCSESS);   
}