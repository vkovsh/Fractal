#include "fractal.h"

void    delete_fractal()
{
    printf("[[Delete]]\n");
    free(g_fractalarray->pixels_array);
    free(g_fractalarray->pixels_addr);
}