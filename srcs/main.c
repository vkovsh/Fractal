#include <stdio.h>

#include "fractal.h"

t_fractalaaray  *g_fractalarray;
t_fractal       *g_f;

// const int checkImageWidth = 512;
// const int checkImageHeight = 512;
// GLubyte checkImage[1024][512];

// static int x_pos, y_pos, x_0, y_0;
// static bool flag;

int main(int argc, char** argv)
{
    t_fractal       f;
    t_retcode       retcode;
    t_fractalaaray  farray;
    
    printf("size = %zu\n", sizeof(t_fractal));
    g_f = &f;
    g_fractalarray = &farray;
    retcode = init_gl(argc, argv);
    if (retcode != RC_SUCSESS)
    {
        printf("retcode = %d\n", retcode);
        exit(retcode);
    }
    retcode = init_fractal(JULIA, 768, 1024, 100);
    if (retcode != RC_SUCSESS)
    {
        printf("retcode = %d\n", retcode);
        exit(retcode);
    }
    set_colors();
    // fill_fractal();
    // fill_fractal_array();

    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion);
    glutPassiveMotionFunc(passive_motion);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}