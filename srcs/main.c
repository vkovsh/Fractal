#include <stdio.h>

#include "fractal.h"

t_fractalaaray  *g_fractalarray;
t_fractal       *g_f;

// const int checkImageWidth = 512;
// const int checkImageHeight = 512;
// GLubyte checkImage[1024][512];

// static int x_pos, y_pos, x_0, y_0;
// static bool flag;

void            draw_triangle(double x1, double y1,
                            double x2, double y2,
                            double x3, double y3,
                            GLfloat r, GLfloat g, GLfloat b)
{
    glBegin(GL_TRIANGLES);
    {
        glColor3f(1, 0, 0); // red
        // glVertex2f( -0.8, -0.8 );
        glVertex2f(x1, y1);
        glColor3f(0, 1, 0); // green
        // glVertex2f( 0.8, -0.8 );
        glVertex2f(x2, y2);
        glColor3f( 0, 0, 1 ); // blue
        // glVertex2f( 0, 0.9 );
        glVertex2f(x3, y3);
    }
    glEnd(); 
}

void    draw_serp(int draw_until_null, double main_x1, double main_y1,
                            double main_x2, double main_y2,
                            double main_x3, double main_y3,
                            GLfloat r, GLfloat g, GLfloat b)
{
    if (draw_until_null <= 0)
        return ;
    double new_x1 = main_x1 + (main_x2 - main_x1) / 2;
    double new_y1 = main_y1 + (main_y2 - main_y1) / 2;
    double new_x2 = main_x2 + (main_x3 - main_x2) / 2;
    double new_y2 = main_y2 + (main_y3 - main_y2) / 2;
    double new_x3 = main_x1 + (main_x3 - main_x1) / 2;
    double new_y3 = main_y1 + (main_y3 - main_y1) / 2;
    draw_triangle(new_x1, new_y1, new_x2, new_y2, new_x3, new_y3, r, g, b);

    // draw_serp(draw_until_null - 1, new_x1, new_y1, new_x2, new_y2, new_x3, new_y3, 1, 1, 1);
    draw_serp(draw_until_null - 1, main_x1, main_y1, new_x1, new_y1, new_x3, new_y3, 1, 0, 0);
    draw_serp(draw_until_null - 1, new_x1, new_y1, main_x2, main_y2, new_x2, new_y2, 0, 1, 0);
    draw_serp(draw_until_null - 1, new_x3, new_y3, new_x2, new_y2, main_x3, main_y3, 0, 0, 1);
    
    // printf("%f %f %f %f %f %f\n", new_x1, new_y1, new_x2, new_y2, new_x3, new_y3);
    
}

void    draw_serp_loop()
{
    glClearColor( 0, 0, 0, 1 );  // (In fact, this is the default.)
    glClear( GL_COLOR_BUFFER_BIT );
    
    // double main_x1 = -0.8;
    // double main_y1 = -0.8;
    // double main_x2 = 0.8;
    // double main_y2 = -0.8;
    // double main_x3 = 0;
    // double main_y3 = 0.9;
    draw_triangle(-0.8, -0.8, 0.8, -0.8, 0, 0.9, 1, 0, 0);
    draw_serp(6, -0.8, -0.8, 0.8, -0.8, 0, 0.9, 1, 1, 1);
    // draw_triangle(main_x1, main_y1, main_x2, main_y2, main_x3, main_y3);

    // double new_x1 = main_x1 + (main_x2 - main_x1) / 2;
    // double new_y1 = main_y1 + (main_y2 - main_y1) / 2;
    // double new_x2 = main_x2 + (main_x3 - main_x2) / 2;
    // double new_y2 = main_y2 + (main_y3 - main_y2) / 2;
    // double new_x3 = main_x1 + (main_x3 - x1) / 2;
    // double new_y3 = y1 + (y3 - y1) / 2;
    // printf("%f %f %f %f %f %f\n", new_x1, new_y1, new_x2, new_y2, new_x3, new_y3);
    // draw_triangle(new_x1, new_y1, new_x2, new_y2, new_x3, new_y3);
    glutSwapBuffers(); // Required to copy color buffer onto the screen.
}

int main(int argc, char** argv)
{
    t_fractal       f;
    t_retcode       retcode;
    t_fractalaaray  farray;
    
    printf("size = %zu\n", sizeof(t_complex));
    printf("size = %zu\n", sizeof(t_fractal));
    g_f = &f;
    g_fractalarray = &farray;
    retcode = init_gl(argc, argv);
    if (retcode != RC_SUCSESS)
    {
        printf("retcode = %d\n", retcode);
        exit(retcode);
    }
    retcode = init_fractal(MANDELBROT, 768, 1024, 100);
    if (retcode != RC_SUCSESS)
    {
        printf("retcode = %d\n", retcode);
        exit(retcode);
    }
    set_colors();
    // fill_fractal();
    // fill_fractal_array();

    glutDisplayFunc(draw_serp_loop);
    // glutReshapeFunc(reshape);
    // glutMotionFunc(motion);
    // glutPassiveMotionFunc(passive_motion);
    // glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}