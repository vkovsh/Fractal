#include "fractal.h"

void    motion(int x, int y)
{
    if (g_f->is_keypressed)
    {
        g_f->x_pos += (x - g_f->x_0);
        g_f->y_pos += (g_f->y_0 - y);
        g_f->x_0 = x;
        g_f->y_0 = y;
        glutPostRedisplay();
    }
}

void    passive_motion(int x, int y)
{
    if (g_f->is_keypressed == false)
    {
        if (g_f->type == JULIA)
        {
            g_julia_arg.re = (x - g_f->width / 2) / (double)(g_f->width / 2);
            g_julia_arg.im = (-y + g_f->height / 2) / (double)(g_f->height / 2);
            // fill_fractal();
            // draw();
            glutPostRedisplay();
        }
    }
}
