#include "fractal.h"

t_retcode   delete_fractal(t_fractal *f)
{
    (void)f;
    // free(f->pixels_addr);
    // free(f->pixels_array);
    return (RC_SUCSESS);
}