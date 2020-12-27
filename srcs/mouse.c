#include <stdio.h>

#include "fractal.h"

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            g_f->is_keypressed = true;
            g_f->x_0 = x;
            g_f->y_0 = y;
        }
        else
        {
            g_f->is_keypressed = false;
        }
    }
    // Wheel reports as button 3(scroll up) and button 4(scroll down)
    else if ((button == 3) || (button == 4)) // It's a wheel event
    {
        // Each wheel event reports like a button click, GLUT_DOWN then GLUT_UP
        if (state == GLUT_UP) return; // Disregard redundant GLUT_UP events
        // printf("Scroll %s At %d %d\n", (button == 3) ? "Up" : "Down", x, y);
        if (button == 3)
        {
            if (g_f->type == MANDELBROT)
            {
                g_f->scale *= (long double)1.1;
		        g_f->x_0 -= (long double)0.1 * (long double)(x - g_f->width / (long double)2 - g_f->x_0);
		        g_f->y_0 -= (long double)0.1 * (long double)(y - g_f->height / (long double)2 - g_f->y_0);
		        printf("%LG %LG\n%LG\n", g_f->x_0, g_f->y_0, g_f->scale);
                if (g_f->iterations < 500)
                    g_f->iterations += 1;
                // fill_fractal();
                glutPostRedisplay();
                // draw();
                printf("%f\n", g_f->scale);
                // printf("%.8x%.8x\n", g_f->scale >> 32, g_f->scale);
            }
            else if (g_f->type == JULIA)
            {
                g_f->iterations++;
                glutPostRedisplay();
            }
        }
        else
        {
            g_f->scale *= 0.9;
		    g_f->x_0 += (double)0.1 * (x - g_f->width / (double)2 - g_f->x_0);
		    g_f->y_0 += (double)0.1 * (y - g_f->height / (double)2 - g_f->y_0);
		    if (g_f->iterations > 40)
                g_f->iterations -= 1;
            // fill_fractal();
            glutPostRedisplay();
            // draw();
            // printf("%d\n", g_f->scale);
        }
        
    }
    else
    {  // normal button event
        printf("Button %s At %d %d\n", (state == GLUT_DOWN) ? "Down" : "Up", x, y);
    }
}