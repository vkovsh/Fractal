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
