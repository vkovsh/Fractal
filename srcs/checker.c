#include <math.h>
#include <stdio.h>

#include "fractal.h"

size_t			in_mandelbrot(t_complex c)
{
	t_complex	o;
	size_t		iter;
	double		tmp;

	tmp = c.re - 0.25;
	if (sqrt(tmp * tmp + c.im * c.im) < 0.5 - 0.5 * cos(atan2(c.im, tmp)))
	{
		return (g_f->iterations);
	}
	o.re = 0;
	o.im = 0;
	// printf("gf = %zu\n", g_f->iterations);
	// printf("[[%f %f]]\n", c.re, c.im);
	for (iter = 0; iter < g_f->iterations; ++iter)
	{
		// printf("[%zu]", iter);
		double re_aquare = o.re * o.re;
		double im_square = o.im * o.im;
		if (re_aquare + im_square > 4)
		{
			break ;
		}
		o.im = 2 * o.re * o.im + c.im;
		o.re = re_aquare - im_square + c.re;
	}
	// printf("iter = %zu\n", iter);
	return (iter);
}